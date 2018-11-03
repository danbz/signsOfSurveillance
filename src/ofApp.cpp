#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    globeRadius = 500;
    int maxSigns = 5;
    for (int i=0; i<maxSigns; i++){
        //ofFile = newPath;
        string newPath;
        newPath = "images/sign" + ofToString(i) + ".jpg";
        
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
    globe.set(globeRadius, 50);
    
    ofDisableArbTex();
    ofLoadImage(globeTexture,"EarthMap_1024x512.jpg");
    
    ofDisableAlphaBlending();
    ofEnableDepthTest();
   // light.enable();
    light.setPosition(ofVec3f(1000,1000,600));
    light.lookAt(ofVec3f(0,0,0));
    
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
    cam.begin();
    ofDrawAxis(600);
    ofDrawRotationAxes(600);
     globeTexture.bind();
    globe.draw();
   // globe.drawWireframe();

    globeTexture.unbind();
    // ofRotateYDeg(rotateY);
    
    for (int i=0; i< signsOfSurveillance.size(); i++){
        ofPushMatrix();
        // ofRotateYDeg(i*(360/signsOfSurveillance.size()));
        // ofTranslate(globeRadius, 0);
        ofVec3f drawLoc = sphericalToCartesian(signsOfSurveillance[i].getLat(), signsOfSurveillance[i].getLong(), globeRadius*1.05f);
        ofDrawCircle(drawLoc.x, drawLoc.y, drawLoc.z, 10);
       // ofTranslate(drawLoc);
        // cout << "drawloc: " << i << " " << drawLoc << endl;
        ofTranslate(0,0,drawLoc.z);
        signsOfSurveillance[i].draw(drawLoc.x, drawLoc.y, 40, 20);
        
        ofPopMatrix();
    }
    
    cam.end();
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

//--------------------------------------------------------------

ofVec3f ofApp::sphericalToCartesian( float lat, float lon, float radius )
{
    ofVec3f result;
    
    lat *= -1;        // inverse latitude.
    lat += 90;        // latitude offset to match geometry of the sphere.
    lon *= -1;        // inverse longitude.
    lon -= 90;        // longitude offset to match geometry of the sphere.
    
        lat *= DEG_TO_RAD;
        lon *= DEG_TO_RAD;
       //  original version
        result.x = radius * sin( lat ) * cos( lon );
        result.y = radius * sin( lat ) * sin( lon );
        result.z = radius * cos( lat );
    
    //    // alternate version from https://stackoverflow.com/questions/1185408/converting-from-longitude-latitude-to-cartesian-coordinates#1185413
    // https://vvvv.org/blog/polar-spherical-and-geographic-coordinates
//
//    lat = ofDegToRad(lat);
//    lon = ofDegToRad(lon);
//    result.x = radius * cos(lat) * cos(lon);
//    result.y = radius * cos(lat) * sin(lon);
//    result.z = radius *sin(lat);
    
    return result;
}
