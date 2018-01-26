#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true); // sync with vertical refresh rate
    
    // ofxGraph uses ofxGui as a internal setting UI
    ofxGuiSetFont(ofToDataPath("ofxGraph/DIN Alternate Bold.ttf"), 10);
    
    // ofxGraph Init
    graph.setup("Sample");
    graph.setDx(1.0); // which means delta of time
    graph.setColor(ofColor::white);  // ofColor(255,255,255)
    
    // multiplotting ofxGraph
    graph_multiplot.setup("Multiplot Sample");
    graph.setDx(1.0);
    graph.setColor(ofColor::azure);
    graph.setLabel({"mouseX","mouseY","framerate"});

}

//--------------------------------------------------------------
void ofApp::update(){
    graph.add(ofRandom(-100,100));
    
    graph_multiplot.add({ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100,100)});
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50,50,50);
    graph.draw();
    graph_multiplot.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 's' ){
        graph.saveSettings(); // save setting graph size and position
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
