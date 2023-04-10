#include "ofApp.h"
#include "ofUtils.h"
#include <iostream>


bool validChar(int key) {
    return 32 <= key && key <= 126; 
}

int clampValue(int value, int min, int max) {
    if (value < min) { return min; }
    if (value > max) { return max; }
    return value;
}


//--------------------------------------------------------------
void ofApp::setup(){
    this->output = "";
    //ofGLProgrammableRenderer myRenderer = ofGLProgrammableRenderer::ofGLProgrammableRenderer(OF_WINDOW);
    this->text = jbLinkedList();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
	ofSetColor(255);
    
    string displayBuffer = text.getString();
    ofDrawBitmapString(displayBuffer, 20, 20, 0);

    int offset = displayBuffer.length();

    ofDrawRectangle(20+((offset-cursorOffset)*8), 7, 2, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //cout << "Key Pressed: " << key;
    if (validChar(key)) {
        //this->text.Append(static_cast<char>(key));
        if (this->text.InsertNegAt(static_cast<char>(key), cursorOffset)) {
            cursorOffset = clampValue(cursorOffset, 0, this->text.getString().length());
        }
        //cout << " Character: " << static_cast<char>(key);
    } else if (key == 8) {
        cout << " BACKSPACING..." << " Cursor Offset: " 
             << cursorOffset << endl;
        if (this->text.DeleteNegAt(cursorOffset)) {
            //cursorOffset--;
            cursorOffset = clampValue(cursorOffset, 0, this->text.getString().length());
        }
    } else if (key == 57356) {
        cursorOffset++;
        cursorOffset = clampValue(cursorOffset, 0, this->text.getString().length());
        cout << " Cursor Offset: " << cursorOffset << endl;
    } else if (key == 57358) {
        cursorOffset--;
        cursorOffset = clampValue(cursorOffset, 0, this->text.getString().length());
        cout << " Cursor Offset: " << cursorOffset << endl;
    }
    
    else {
        cout << " INVALID CHARACTER";
    }

    cout << " Buffer: " << this->text.getString() << endl;
}
