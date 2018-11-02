#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    int maxSigns = 3;
    for (int i=0; i<maxSigns; i++){
        //ofFile = newPath;
        string newPath;
        newPath = "sign" + ofToString(i) + ".jpg";
        
//        if (newPath.exists()){
//            ofLogVerbose("The file exists - now checking the type via file extension");
//            string fileExtension = ofToUpper(newPath.getExtension());
//
//            //We only want text
//            if (fileExtension == "jpg") {
//
//                // load the image file
                sign newSign;
                newSign.load(newPath);
                signsOfSurveillance.push_back(newSign);
                
//            }
//        }
//
   }
    
    rotateY = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    if (rotateY < 360){
        rotateY++;
    } else {
        rotateY =0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
   // ofRotateYDeg(rotateY);
    for (int i=0; i< signsOfSurveillance.size(); i++){
        ofPushMatrix();
        ofRotateYDeg(i*(360/signsOfSurveillance.size()));
        
        signsOfSurveillance[i].draw(0, 0 , 400, 200);
        
        ofPopMatrix();
    }
    cam.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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


//--------------------------------------------------------------


sign::sign(){  // sign constructor
    
    // load image from supplied path
    
    // load xml
    
    
    // extract lat long etc from XML
    
}

//--------------------------------------------------------------

sign::~sign(){    // sign destuctor

}

//--------------------------------------------------------------

void sign::load(string imagePath){
    cout << "loading: " << ofToString(imagePath) << endl;
    image.load(imagePath);
    
    // load XML from jpg
     exifData =  getEXIF(imagePath);
}

//--------------------------------------------------------------

bool sign::isLandscape(){
    // return bool for image orientation
};

//--------------------------------------------------------------

float sign::getLat(){
    return exifData.GeoLocation.Latitude;
};

//--------------------------------------------------------------

float sign::getLong(){
  return  exifData.GeoLocation.Longitude;
};

//--------------------------------------------------------------

float sign::getDate(){
    
};

//--------------------------------------------------------------

string sign::getTime(){
    return exifData.DateTimeOriginal;
};

//--------------------------------------------------------------

string sign::getCountry(){
    // calculate country
};

//--------------------------------------------------------------

void sign::draw(int x, int y, int width, int height){
    
    string latLong;
    latLong = ofToString(exifData.GeoLocation.Latitude) + ", " + ofToString(exifData.GeoLocation.Longitude);
    latLong += " orientation: " + ofToString(exifData.Orientation);

  //  image.rotate90(1);
    
    image.draw( x,  y, width, height);
    ofDrawBitmapString(ofToString(exifData.DateTimeOriginal), x, y + height+20);
    ofDrawBitmapString(latLong, x, y + height + 40);
    
    // Image orientation, start of data corresponds to
    // 0: unspecified in EXIF data
    // 1: upper left of image
    // 3: lower right of image
    // 6: upper right of image
    // 8: lower left of image
    // 9: undefined
};
