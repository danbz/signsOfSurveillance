#pragma once

#include "ofMain.h"
#include "ofxExif.h"
#include "ofxGui.h"

static ofTrueTypeFont signFont;

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
    void draw(int x, int y, int z, int width, int height);
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
    
    ofVec3f sphericalToCartesian( float lat, float lon, float radius );
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void sortSigns();
    static  bool sortDescending(const sign &i, const sign &j);
    
    vector<sign> signsOfSurveillance;
    float rotateY;
    int globeRadius;
    
    ofSpherePrimitive globe;
    ofTexture globeTexture;
    ofEasyCam cam;
    ofLight light;
    
    bool b_drawGui, b_rotate;
    
   // int signWidth, signHeight, signDist;
    
    ofxPanel gui;
    ofxFloatSlider signWidth, signHeight, signDist;
    
};
