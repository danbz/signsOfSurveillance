#pragma once

#include "ofMain.h"
#include "ofxExif.h"

class sign {
    public :
    
    ofImage image;
    easyexif::EXIFInfo exifData;
    
    sign(); // sign constructor
    
    ~sign(); //sign destructor
    
    bool isLandscape(); // getter and setter functions
    float getLat();
    float getLong();
    float getDate();
    string getTime();
    void draw(int x, int y, int width, int height);
    void load(string filePath);
    string getCountry();
    
    private :
    
};

class ofApp : public ofBaseApp{
    

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    vector<sign> signsOfSurveillance;
    int rotateY;
    
    ofEasyCam cam;
    
    
};
