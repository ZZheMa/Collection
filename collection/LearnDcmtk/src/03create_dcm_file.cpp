#include <iostream>
#include <string>
#include <list>
#include <cassert>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

void CreateDcmFile() {
  DcmFileFormat file_format;
  DcmDataset* dataset = file_format.getDataset();

  dataset->print(std::cout);

  char uid[100] = { 0 };
  dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid, SITE_INSTANCE_UID_ROOT));
  dataset->putAndInsertString(DCM_SOPClassUID, UID_CTImageStorage);
  dataset->putAndInsertString(DCM_PatientName, "Zhe^Ma");

  dataset->print(std::cout);

  file_format.saveFile("test.dcm", EXS_LittleEndianExplicit);
}

void ConvertCharacterSet() {
  const std::string kDir = "C:\\Users\\Admin\\Desktop\\dicom data\\";

  DcmFileFormat file_format;
  OFCondition cond = file_format.loadFile(kDir + "zhe.dcm", EXS_Unknown, EGL_noChange, DCM_MaxReadLength, ERM_autoDetect);
  file_format.loadAllDataIntoMemory();

  std::string dst_character = "ISO_IR 100";
  cond = file_format.convertCharacterSet("ISO_IR 192", dst_character);
  DcmDataset* dataset = file_format.getDataset();
  char uid[100] = "";
  //dataset->putAndInsertString(DCM_SOPInstanceUID, dcmGenerateUniqueIdentifier(uid));
  dataset->putAndInsertString(DCM_SpecificCharacterSet, dst_character.c_str());
  //dataset->putAndInsertString(DCM_PatientID, "2018060802");

  cond = file_format.saveFile(kDir + "\\05.dcm", EXS_Unknown, EET_ExplicitLength, EGL_recalcGL, EPD_noChange, 0, 0, EWM_updateMeta);

}

int main() {
  //CreateDcmFile();
  ConvertCharacterSet();


  return 0;
}
