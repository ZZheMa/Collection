#include <iostream>
#include <vector>

#include "dcmtk/config/osconfig.h"
#include "dcmtk/dcmdata/dctk.h"

#define N 2

static void Test1() {
  DcmDataset dataset;

  for (int i = 1; i <= N; ++i) {
    DcmItem* step_item = NULL;
    dataset.findOrCreateSequenceItem(DCM_ScheduledStepAttributesSequence, step_item);

    char buf[256] = { 0 };
    sprintf(buf, "study_instance_uid%d", i);
    step_item->putAndInsertString(DCM_StudyInstanceUID, buf);
    sprintf(buf, "requested_procedure_description%d", i);
    step_item->putAndInsertString(DCM_RequestedProcedureDescription, buf);
  }

  dataset.print(std::cout);
}

static void Test2() {
  DcmDataset dataset;

  for (int i = 1; i <= N; ++i) {
    DcmSequenceOfItems* step_item = new DcmSequenceOfItems(DCM_ScheduledStepAttributesSequence);

    //char buf[256] = { 0 };
    //sprintf(buf, "study_instance_uid%d", i);
    //step_item->putAndInsertString(DCM_StudyInstanceUID, buf);
    //sprintf(buf, "requested_procedure_description%d", i);
    //step_item->putAndInsertString(DCM_RequestedProcedureDescription, buf);
    OFCondition cond = dataset.insert(step_item);  // 第二次添加时失败，在dataset中其是唯一的。
  }

  dataset.print(std::cout);
}

static void Test3() {
  DcmDataset dataset;

  DcmSequenceOfItems* step_item = new DcmSequenceOfItems(DCM_ScheduledStepAttributesSequence);
  for (int i = 1; i <= N; ++i) {
    DcmItem* item = new DcmItem;

    char buf[256] = { 0 };
    sprintf(buf, "study_instance_uid%d", i);
    item->putAndInsertString(DCM_StudyInstanceUID, buf);
    sprintf(buf, "requested_procedure_description%d", i);
    item->putAndInsertString(DCM_RequestedProcedureDescription, buf);

    step_item->append(item);
  }

  dataset.insert(step_item);

  dataset.print(std::cout);
}

static void Test4() {
  DcmDataset dataset;

  for (int i = 1; i <= N; ++i) {
    DcmItem* step_item = NULL;

    dataset.findOrCreateSequenceItem(DCM_ScheduledStepAttributesSequence, step_item, i - 1);

    char buf[256] = { 0 };
    sprintf(buf, "study_instance_uid%d", i);
    step_item->putAndInsertString(DCM_StudyInstanceUID, buf);
    sprintf(buf, "requested_procedure_description%d", i);
    step_item->putAndInsertString(DCM_RequestedProcedureDescription, buf);
  }

  dataset.print(std::cout);
}

static void TestVectorSizeType() {
  std::vector<int> vec;
  for (int i = 0; i < vec.size(); i++) {  // warning
    //vector.size 返回size_t.
  }
}

static void MainTest() {
  FILE* fp = freopen("result.txt", "w", stdout);

  std::cout << "------------------------Test1----------------------";
  // 1.使用findOrCreateSequenceItem，后面的数据会覆盖前面的数据。
  Test1();

  std::cout << "\n\n\n------------------------Test2----------------------";
  Test2();

  std::cout << "\n\n\n------------------------Test3----------------------";
  Test3();

  std::cout << "\n\n\n------------------------Test4----------------------";
  Test4();

  fclose(fp);
}

int main2(int argc, char *argv[]) {
  MainTest();

  return 0;
}
