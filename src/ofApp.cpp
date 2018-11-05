#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    globeRadius = 500;
   // int maxSigns = 5;
//    for (int i=0; i<maxSigns; i++){
//        //ofFile = newPath;
//        string newPath;
//        newPath = "images/sign" + ofToString(i) + ".jpg";
//
////        if (newPath.exists()){
////            ofLogVerbose("The file exists - now checking the type via file extension");
////            string fileExtension = ofToUpper(newPath.getExtension());
////
////            //We only want text
////            if (fileExtension == "jpg") {
////
////                // load the image file
//                sign newSign;
//                newSign.load(newPath);
//                signsOfSurveillance.push_back(newSign);
//
////            }
////        }
////
//   }
    
    rotateY = 0.0f;
    globe.set(globeRadius, 50);
    
    ofDisableArbTex();
    //ofLoadImage(globeTexture,"EarthMap_1024x512.jpg");
    //  ofLoadImage(globeTexture,"high-resolution-political-world-map.jpg");
    ofLoadImage(globeTexture,"world_shaded_43k-med.jpg");
    globeTexture.generateMipmap();
    
    ofDisableAlphaBlending();
    ofEnableDepthTest();
   // light.enable();
    light.setPosition(ofVec3f(1000,1000,600));
    light.lookAt(ofVec3f(0,0,0));
    b_rotate = false;
    
    signFont.load( "sans-serif",  12);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (b_rotate) {
        if (rotateY < 360){
            rotateY+=0.05;
        } else {
            rotateY =0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    cam.begin();
    ofPushMatrix();

   // ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateYDeg(rotateY);
    ofDrawAxis(600);
    // ofDrawRotationAxes(600);
     globeTexture.bind();
    globe.draw();
   // globe.drawWireframe();

    globeTexture.unbind();
    
//    for (int i=0; i< signsOfSurveillance.size(); i++){
//       ofPushMatrix();
//        // ofRotateYDeg(i*(360/signsOfSurveillance.size()));
//        // ofTranslate(globeRadius, 0);
//        ofVec3f drawLoc = sphericalToCartesian(signsOfSurveillance[i].getLat(), signsOfSurveillance[i].getLong(), globeRadius*1.05f);
//
//        ofDrawCircle(drawLoc.x, drawLoc.y, drawLoc.z, 10);
//       // ofTranslate(drawLoc);
//        // cout << "drawloc: " << i << " " << drawLoc << endl;
//        ofTranslate(0,0,drawLoc.z);
//        signsOfSurveillance[i].draw(drawLoc.x, drawLoc.y, 40, 20);
//
//        ofPopMatrix();
//    }
    
    
    /// new quaternion stuff
    //translate so that the center of the screen is 0,0
    
    ofSetColor(255, 255, 255, 20);
    //draw a translucent wireframe sphere (ofNoFill() is on)
    ofPushMatrix();
    //add an extra spin at the rate of 1 degree per frame
   // ofRotateDeg(ofGetFrameNum(), 0, 1, 0);
    //ofDrawSphere(0, 0, 0, 300);
    ofPopMatrix();
    
    ofSetColor(255);
    for(unsigned int i = 0; i < signsOfSurveillance.size(); i++){
        
        //three rotations
        //two to represent the latitude and lontitude of the city
        //a third so that it spins along with the spinning sphere
        ofQuaternion latRot, longRot, spinQuat;
        
        float lat = signsOfSurveillance[i].getLat();
        float lon = signsOfSurveillance[i].getLong();
        lat *= -1;        // inverse latitude.
       // lat += 90;        // latitude offset to match geometry of the sphere.
       // lon *= -1;        // inverse longitude.
        lon += 180;        // longitude offset to match geometry of the sphere.
        latRot.makeRotate(lat , 1, 0, 0);
        longRot.makeRotate(lon, 0, 1, 0);
        spinQuat.makeRotate(0, 0, 1, 0);
        
        //our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
        ofVec3f center = ofVec3f(0,0,510);
        //multiplying a quat with another quat combines their rotations into one quat
        //multiplying a quat to a vector applies the quat's rotation to that vector
        //so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
        ofVec3f worldPoint = latRot * longRot * spinQuat * center;
        
        //draw it and label it
        ofDrawLine(ofVec3f(0,0,0), worldPoint);
        
        //set the bitmap text mode billboard so the points show up correctly in 3d
       // ofDrawBitmapString(signsOfSurveillance[i].getTime(), worldPoint );
       // ofTranslate(0,0,worldPoint.z);
        signsOfSurveillance[i].draw(worldPoint.x, worldPoint.y, worldPoint.z, 40, 20);
        
    }
    
    ofPopMatrix();
    
    cam.end();
    ofDrawBitmapString(ofToString( cam.getPosition() ), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch (key) {
        case 'g':
        case 'G':
            b_drawGui =!b_drawGui;
            break;
            
        case 'f':
        case 'F':
            ofToggleFullscreen();
            
            break;
            
        case 'r':
            b_rotate = !b_rotate;
            break;
            
        case 'l':
            //Open the Open File Dialog to load text file
            ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a folder with jpg image files");
            
            //Check if the user opened a file
            if (openFileResult.bSuccess){
                ofLogVerbose("User selected a folder");
                //We have a file, check it and process it
                processOpenFileSelection(openFileResult);
                
            }else {
                ofLogVerbose("User hit cancel");
            }
            break;
    }
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
}

//--------------------------------------------------------------

float sign::getLat(){
    return exifData.GeoLocation.Latitude;
}

//--------------------------------------------------------------

float sign::getLong(){
  return  exifData.GeoLocation.Longitude;
}

//--------------------------------------------------------------

float sign::getDate(){
    
}

//--------------------------------------------------------------

string sign::getTime(){
    return exifData.DateTimeOriginal;
};

//--------------------------------------------------------------

string sign::getCountry(){
    // calculate country
}

//--------------------------------------------------------------

void sign::draw(int x, int y, int z, int width, int height){
    
    string latLong;
    latLong = ofToString(exifData.GeoLocation.Latitude) + ", " + ofToString(exifData.GeoLocation.Longitude);
    //latLong += " orientation: " + ofToString(exifData.Orientation);

  //  image.rotate90(1);
    
    image.draw( x,  y, z, width, height);
   // ofDrawBitmapString(ofToString(exifData.DateTimeOriginal), x, y + height+20);
    // ofDrawBitmapString(latLong, x, y + height + 10);
    ofPushMatrix();
    ofTranslate(0,0,z);
    signFont.drawString(latLong, x, y + height + 10);
    ofPopMatrix();
    // Image orientation, start of data corresponds to
    // 0: unspecified in EXIF data
    // 1: upper left of image
    // 3: lower right of image
    // 6: upper right of image
    // 8: lower left of image
    // 9: undefined
}

//--------------------------------------------------------------

ofVec3f ofApp::sphericalToCartesian( float lat, float lon, float radius ){
    ofVec3f result;
    
//    lat *= -1;        // inverse latitude.
//    lat += 90;        // latitude offset to match geometry of the sphere.
//    lon *= -1;        // inverse longitude.
//    lon -= 90;        // longitude offset to match geometry of the sphere.
//
//    lat *= DEG_TO_RAD;
//    lon *= DEG_TO_RAD;
//    //  original version
//    result.x = radius * sin( lat ) * cos( lon );
//    result.y = radius * sin( lat ) * sin( lon );
//    result.z = radius * cos( lat );
//
//
//
//
//    return result;
    // new quaternion example

    //three rotations
    //two to represent the latitude and lontitude of the city
    //a third so that it spins along with the spinning sphere
    ofQuaternion latRot, longRot, spinQuat;
    latRot.makeRotate(lat, 1, 0, 0);
    longRot.makeRotate(lon, 0, 1, 0);
    spinQuat.makeRotate(0, 0, 1, 0);
    
    //our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
    ofVec3f center = ofVec3f(0,0,600);
    //multiplying a quat with another quat combines their rotations into one quat
    //multiplying a quat to a vector applies the quat's rotation to that vector
    //so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
    ofVec3f worldPoint = latRot * longRot * spinQuat * center;
    
    //draw it and label it
    ofDrawLine(ofVec3f(0,0,0), worldPoint);
    
    //set the bitmap text mode billboard so the points show up correctly in 3d
   // ofDrawBitmapString(cities[i].name, worldPoint );
    return worldPoint;
}

//--------------------------------------------------------------


void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    
    ofFile file (openFileResult.getPath());
    ofFilePath dirPath;
    dirPath.getPathForDirectory(openFileResult.getPath());
    
    if (file.exists()){
        
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        
        //We only want jpg images
        if (fileExtension == "JPG") {
            
           // ofDirectory imageDirectory(ofToDataPath(dirPath));
            ofDirectory imageDirectory("images");

            imageDirectory.listDir();
            imageDirectory.allowExt("jpg");
            imageDirectory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
            
            for (int i=0; i<imageDirectory.size(); i++){
           
                sign newSign;
                newSign.load(imageDirectory.getPath(i));
                newSign.image.resize(newSign.image.getWidth()/10, newSign.image.getHeight()/10);
                signsOfSurveillance.push_back(newSign);
  
            }
        }
    }
}
