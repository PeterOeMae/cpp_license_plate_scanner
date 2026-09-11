#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

    ofBackground(40);
    ofSetColor(255);

    if (imageLoaded) {

        float frameSize = 250.0f;
        float spacing = 20.0f;

        float startX = 20.0f;
        float startY = 40.0f;

        drawImageInFrame(selectedImage, startX, startY, frameSize);

        float imageScale = std::min(frameSize / selectedImage.getWidth(), frameSize / selectedImage.getHeight());

        float displayedWidth = selectedImage.getWidth() * imageScale;
        float displayedHeight = selectedImage.getHeight() * imageScale;

        float offsetX = startX + (frameSize - displayedWidth) / 2.0f;
        float offsetY = startY + (frameSize - displayedHeight) / 2.0f;

        ofNoFill();
        ofSetColor(255, 0, 0);

        for (const auto &box : candidateBoxes) {

            float x = offsetX + box.x * imageScale;
            float y = offsetY + box.y * imageScale;
            float w = box.width * imageScale;
            float h = box.height * imageScale;

            ofDrawRectangle(x, y, w, h);
        }

        ofFill();
        ofSetColor(255);


        drawImageInFrame(grayPreview, startX + frameSize + spacing, startY, frameSize);
        drawImageInFrame(blurredPreview, startX + (frameSize + spacing) * 2, startY, frameSize);
        drawImageInFrame(edgePreview, startX + (frameSize + spacing) * 3, startY, frameSize);

        float infoY = startY + frameSize + 20.0f;

        std::string info = "File: " + selectedFilename + "\nResolution: " + ofToString(selectedImage.getWidth()) + " x " + ofToString(selectedImage.getHeight());

        ofSetColor(255);
        ofDrawBitmapString("Press O to open another image", 20, 20);
        ofDrawBitmapString(info, startX, infoY);

    } else {

        ofDrawBitmapString("Press O to open an image", 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::drawImageInFrame(ofImage &image, float x, float y, float frameSize) {

    if (!image.isAllocated()) {
        return;
    }

    ofSetColor(0);
    ofDrawRectangle(x, y, frameSize, frameSize);

    float scale = std::min(frameSize / image.getWidth(), frameSize / image.getHeight());

    float drawWidth = image.getWidth() * scale;
    float drawHeight = image.getHeight() * scale;

    float drawX = x + (frameSize - drawWidth) / 2.0f;
    float drawY = y + (frameSize - drawHeight) / 2.0f;

    ofSetColor(255);
    image.draw(drawX, drawY, drawWidth, drawHeight);
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

    if (key == 'o' || key == 'O') {

        ofFileDialogResult result = ofSystemLoadDialog("Upload Image");

        if (result.bSuccess) {

            if (selectedImage.load(result.getPath())) {

                selectedFilename = ofFilePath::getFileName(result.getPath());

                ofPixels &pixels = selectedImage.getPixels();

                cv::Mat colorImage(selectedImage.getHeight(), selectedImage.getWidth(), CV_8UC3, pixels.getData());

                cv::cvtColor(colorImage, grayImage, cv::COLOR_RGB2GRAY);
                grayPreview.setFromPixels(grayImage.data, grayImage.cols, grayImage.rows, OF_IMAGE_GRAYSCALE);

                cv::GaussianBlur(grayImage, blurredImage, cv::Size(5, 5), 0);
                blurredPreview.setFromPixels(blurredImage.data, blurredImage.cols, blurredImage.rows, OF_IMAGE_GRAYSCALE);

                cv::Canny(blurredImage, edgeImage, 50, 150);
                edgePreview.setFromPixels(edgeImage.data, edgeImage.cols, edgeImage.rows, OF_IMAGE_GRAYSCALE);

                candidateBoxes.clear();
                std::vector<std::vector<cv::Point>> contours;
                cv::findContours(edgeImage, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
                for (const auto &contour : contours) {
                    cv::Rect box = cv::boundingRect(contour);
                    candidateBoxes.push_back(box);
                    
                    float aspectRatio = static_cast<float>(box.width) / box.height;
                    int area = box.width * box.height;

                    if (box.width > 60 &&
                        box.height > 15 &&
                        aspectRatio > 2.0f &&
                        aspectRatio < 6.0f &&
                        area > 1500) {

                        candidateBoxes.push_back(box);
                    }
                }

                imageLoaded = true;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}