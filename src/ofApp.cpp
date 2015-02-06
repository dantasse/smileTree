#include "ofApp.h"

ofxProcTree* getNewTree(int input) {
    ofxProcTreeBranch::Properties * p = new ofxProcTreeBranch::Properties();
    if (input > 6) input = 6; // clamp it to avoid drawing an exponentially complicated tree
    p->seed = rand() % 1000;
    p->segments = 7;
    p->levels = input;//5;
    p->vMultiplier = 1.01;
    p->twigScale = 0;
    p->initalBranchLength = 1.5;
    p->lengthFalloffFactor = 0.73;
    p->lengthFalloffPower = 0.76;
    p->clumpMax = 0.53;
    p->clumpMin = 0.419;
    p->branchFactor = 3.4;
    p->dropAmount = -0.16;
    p->growAmount = .619;
    p->sweepAmount = 0.01;
    p->maxRadius = 0.168;
    p->climbRate = 0.472;
    p->trunkKink = 0.06;
    p->treeSteps = 5;
    p->taperRate = 0.835;
    p->radiusFalloffRate = 0.73;
    p->twistRate = 2.29;
    p->trunkLength = 2.2;
    
    return new ofxProcTree(p);
}
//--------------------------------------------------------------
void ofApp::setup(){
    
    tree = getNewTree(1);
    
    cam.setPosition(0, 0, -400);
    cam.setOrientation(ofVec3f(0,0,0));
    cam.lookAt(ofVec3f(0,0,0));
    
    pointLight.setPointLight();
    pointLight.setPosition(-200, 100, -200);
    pointLight.setDiffuseColor(ofFloatColor(0.8,0.7,0.9,1.0));
    
    dirLight.setDirectional();
    dirLight.setPosition(0, 0, -400);
    dirLight.lookAt(ofVec3f(0,0,0));
    
    //ofViewport(ofRectangle(-1,-1,2,2)); // Normalize viewport
    //ofSetupScreenPerspective(2,2);
    
    ofSetVerticalSync(true);
    ofSetFrameRate(120);
    webcam.initGrabber(640, 480);
    smile.setup();
}

int smileLength = 0;
float threshold = 0.4;
float smileyness = 0.0; // for smoothing
//--------------------------------------------------------------
void ofApp::update(){

    webcam.update();
    if(webcam.isFrameNew()) {
        smile.update(webcam);
        if(smile.getFaceFound()) {
            float cur = smile.getSmileAmount();
            graph.add(cur);

            if (isnan(smileyness)) {
                // first couple of readings are NAN, got to make sure that doesn't hose us
                smileyness = 0;
            }
            smileyness = 0.5*graph.getNormalized(cur) + 0.5 * smileyness;
            
            //ofLog() << graph.getNormalized(cur) << ", " << cur << ", " << smileyness << ", " << threshold;
            ofLog() << smileyness;
            if (smileyness > threshold) {
                smileLength += 1;
            } else {
                // smile just ended
                if (smileLength > 0) {
                    tree = getNewTree(smileLength / 10);
                    smileLength = 0;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw the tree.
    cam.lookAt(ofVec3f(0,0,0));
    
    ofBackgroundGradient(ofColor(0), ofColor(40));
    ofSetColor(255);
    
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight.enable();
    
    ofPushMatrix();
    ofScale(80,80,80);
    
    ofTranslate(0, -tree->mesh.getCentroid().y, 0);
    ofRotateY(ofGetElapsedTimef());
    
    tree->mesh.draw();

    pointLight.disable();
    ofDisableDepthTest();
    ofPopMatrix();
    ofDisableLighting();
    cam.end();

    ofSetColor(200);
    ofDrawBitmapString("smile to draw a tree - the longer the smile, the better the tree", 20, 20);

    // Draw the webcam area and graph.
    ofTranslate(0, 30);
    webcam.draw(0, 0, 320, 240);
//    smile.draw();

    ofTranslate(0, 240);
    ofSetColor(0);
    ofRect(0, 0, 300, 100);
    ofSetColor(255);
    graph.draw(300, 100);
    
}

//--------------------------------------------------------------
int numTimesPressed = 0;
void ofApp::keyPressed(int key){
    if (key == 'n') {
        tree = getNewTree(numTimesPressed++);
    }
}
