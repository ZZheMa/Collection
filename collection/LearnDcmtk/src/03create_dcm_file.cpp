#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

int main() {
  DcmFileFormat file_format;
  DcmDataset* dataset = file_format.getDataset();

  dataset->print(std::cout);

  char uid[100] = { 0 };
  dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
  dataset->putAndInsertString(DCM_SOPClassUID, UID_CTImageStorage);
  dataset->putAndInsertString(DCM_PatientName, "Zhe^Ma");

  dataset->print(std::cout);

  file_format.saveFile("test.dcm", EXS_LittleEndianExplicit);

  return 0;
}
