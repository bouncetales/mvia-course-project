#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
struct MouseEventParamData {
  std::vector<cv::Point>* data;
  cv::Mat* image;
  int num_mouse_click;
};
static void MouseEventCallback(int event, int x, int y, int flags, void* param) {
  std::vector<cv::Point>& data = *(std::vector<cv::Point>*)((MouseEventParamData *)param)->data;
  cv::Mat& image = *(cv::Mat*)((MouseEventParamData *)param)->image;
  int& num_clicked = ((MouseEventParamData *)param)->num_mouse_click;
  switch (event) {
  case cv::EVENT_LBUTTONDOWN:
    if (x < 0 || y < 0) {
      std::cout << x << "," << y << std::endl;
    }
    cv::Point pt(x, y);
    data.push_back(pt);
    cv::circle(image, pt, 1, cv::Scalar(255, 0, 0), cv::FILLED);
    ++num_clicked;
  }
}
void TestReadData(cv::String filename);
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: collect_data <filename>\n"
      "Suffix of filename should be .json or .yaml " << std::endl;
    return -1;
  }
  // Prepare data container
  std::vector<cv::Point > data;
  // Draw plate
  cv::Mat image(600, 800, CV_8UC3, cv::Scalar(255, 255, 255));
  MouseEventParamData param;
  param.data = &data;
  param.image = &image;
  cv::String window_name("Data Collect");
  cv::namedWindow(window_name, cv::WINDOW_NORMAL);
  cv::setMouseCallback(window_name, MouseEventCallback, &param);
  while (true) {
    imshow(window_name, image);
    char c = (char) cv::waitKey(10);
    if (c ==  27) break;
  }
  // for (auto it = data.begin(); it != data.end(); ++it) {
  //   std::cout << *it;
  // }
  // std::cout << std::endl;
  cv::FileStorage fs;
  cv::String filename(argv[1]);
  if (!fs.open(filename, cv::FileStorage::WRITE)) {
        // error message
    std::cout << "Cannot open file: " << filename << std::endl;
    return -1;
  }
  cv::write(fs, "data", data);
  fs.release();
  TestReadData(filename);
  return 0;
}
// Please refer this code to read data from file
void TestReadData(cv::String filename) {
  // Prepare data container
  std::vector<cv::Point > ptdata;
  cv::FileStorage fs;
  if (!fs.open(filename, cv::FileStorage::READ)) {
    // error message
    std::cout << "Cannot open file: " << filename << std::endl;
    return;
  }
  cv::FileNode data_node = fs["data"];
  for (cv::FileNodeIterator it = data_node.begin(); it != data_node.end(); ) {
    int a, b;
    *it++ >> a;
    *it++ >> b;
    ptdata.push_back(cv::Point2i(a, b));
  }
  fs.release();
  for (auto it = ptdata.begin(); it != ptdata.end(); ++it) {
    std::cout << *it;
  }
  std::cout << std::endl;
}
