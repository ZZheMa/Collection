#include <iostream>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

static const char* kFilePath = "C:\\Users\\Admin\\Desktop\\New folder\\DcmToDis\\@44.dcm";

static void PrintAllTagInfos(DcmItem* item, int space_count = 0) {
  if (item == NULL) {
    return;
  }

  DcmObject* element = item->nextInContainer(NULL);
  if (element == NULL) {
    return;
  }

  while (element != NULL) {
    DcmTag tag = element->getTag();
    DcmTagKey tag_key = tag.getXTag();

    OFString tag_value;
    item->findAndGetOFString(tag_key, tag_value);

    const char* tag_name = tag.getTagName();

    std::cout << std::string(space_count, ' ') << tag_key << tag_name << "\t" << tag_value << std::endl;

    if (tag.getEVR() == EVR_SQ) {
      DcmItem* squence_item = NULL;
      item->findAndGetSequenceItem(tag_key, squence_item);
      PrintAllTagInfos(squence_item, space_count + 1);
    }

    element = item->nextInContainer(element);
  }
}

int main1(int argc, char *argv[]) {
  DcmFileFormat file_format;
  OFCondition oc = file_format.loadFile(kFilePath);
  if (oc.bad()) {
    return 1;
  }

  DcmDataset* dataset = file_format.getDataset();
  DcmMetaInfo* meta_info = file_format.getMetaInfo();

  //PrintAllTagInfos(meta_info);
  //PrintAllTagInfos(dataset);

  //dataset->print(std::cout);
  meta_info->print(std::cout);

  //if (oc.good()) {
  //  OFString patientName;
  //  if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good()) {
  //    std::cout << "Patient Name:" << patientName.data() << std::endl;;
  //  }
  //}

  return 0;
}
