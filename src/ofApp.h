#pragma once

#include "ofMain.h"
#include "PlateCandidateScorer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/geometry.hpp>

class ofApp : public ofBaseApp {

public:

    void setup() override;
    void update() override;
    void draw() override;
    void exit() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;

    void drawImageInFrame(ofImage &image, float x, float y, float frameSize);

	PlateCandidateScorer plateScorer;

    ofImage selectedImage;
    ofImage grayPreview;
    ofImage blurredPreview;
    ofImage edgePreview;

	cv::Mat colorImage;
    cv::Mat grayImage;
    cv::Mat blurredImage;
    cv::Mat edgeImage;
	std::vector<cv::Rect> candidateBoxes;

	cv::Rect bestPlateBox;
	bool plateFound = false;

    bool imageLoaded = false;
    std::string selectedFilename;

};