#include "PlateOCR.h"

PlateOCR::PlateOCR() {

}

PlateOCR::~PlateOCR() {
    tess.End();
}

bool PlateOCR::setup() {

    if (tess.Init("C:/msys64/mingw64/share/tessdata", "eng")) {
        std::cout << "ERROR: Could not initialize Tesseract." << std::endl;
        return false;
    }

    tess.SetPageSegMode(tesseract::PSM_SINGLE_LINE);
    tess.SetVariable("tessedit_char_whitelist", "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    std::cout << "Tesseract initialized successfully." << std::endl;

    return true;
}

std::string PlateOCR::recognize(const cv::Mat &image) {

    if (image.empty()) {
        return "";
    }

    tess.SetImage(image.data,image.cols,image.rows,image.channels(),static_cast<int>(image.step));

    char *result = tess.GetUTF8Text();

    if (result == nullptr) {
        return "";
    }

    std::string text(result);

    delete[] result;

    return text;
}


