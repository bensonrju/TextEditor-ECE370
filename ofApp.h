#pragma once

#include "ofMain.h"
#include "jbLinkedList.h"
#include <string>

class ofApp : public ofBaseApp{
	private:
		
		string output; 
		ofTrueTypeFont outputText;
		ofCairoRenderer myRenderer;
		int cursorOffset = 0;

	public:
		jbLinkedList text;

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
};
