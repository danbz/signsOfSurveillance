#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // set up sign sizes and distance from globe surface
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    gui.setup();
    gui.add(signScale.setup("signWidth", 10.0, 1.0, 20.0));
    gui.add(signDist.setup("signDist", 10.0, 1.0, 20.0));
    globeRadius = 2000;
    rotateY = 0.0f;
    globe.set(globeRadius, 100);
    
    ofDisableArbTex();
    // ofLoadImage(globeTexture,"EarthMap_1024x512.jpg");
    // ofLoadImage(globeTexture,"high-resolution-political-world-map.jpg");
    ofLoadImage(globeTexture,"world_shaded_43k-med.jpg");
    globeTexture.generateMipmap();
    
    ofDisableAlphaBlending();
    ofEnableDepthTest();
    // light.enable();
    light.setPosition(ofVec3f(2000,2000,1200));
    light.lookAt(ofVec3f(0,0,0));
    b_rotate = false;
    
    signFont.load("FuturaLT.ttf", 6);
    signFont.setGlobalDpi(192);
    if  (!signFont.isLoaded()) {
        cout << "font failed to load" << endl;
    }
    
    cam.setDistance(2400);
    cam.setPosition(-300, 1720, -1650); // set camera looking at europe
    cam.setTarget(globe);
    rotateSpeed = 0.02;
}

//--------------------------------------------------------------
void ofApp::update(){
    int camDist = cam.getDistance();
    if (camDist < globeRadius + 7) {
        ofVec3f camPos = cam.getPosition();
        cam.setDistance( globeRadius +7);
    }
    signScale = ((camDist - globeRadius)/5.0) + 5 ; // scale signs dependent upon camera distance from globe
    signDist = ((camDist - globeRadius)/10.0) + 5;
    
    if (b_rotate) {
        if (rotateY < 360){
            rotateY+=rotateSpeed;
        } else {
            rotateY =0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    cam.begin();
    ofRotateYDeg(rotateY);
    ofDrawAxis(600);
    // ofDrawRotationAxes(600);
    globeTexture.bind();
    globe.draw();
    // globe.drawWireframe();
    globeTexture.unbind();
   // ofSetColor(255, 255, 255, 100);
    
    ofVec3f worldPoint;
    for(unsigned int i = 0; i < signsOfSurveillance.size(); i++){
        worldPoint =  sphericalToCartesian(signsOfSurveillance[i].getLat(), signsOfSurveillance[i].getLong(), globeRadius+signDist);
        ofDrawLine(ofVec3f(0,0,0), worldPoint);
       
        signsOfSurveillance[i].draw(worldPoint.x, worldPoint.y, worldPoint.z, signScale);
    }
    cam.end();
    
    if (b_drawGui){
        ofSetColor(255);
        gui.draw();
        ofDrawBitmapString( " camdistance: " + ofToString( cam.getDistance()) +  "\n pos:" +  ofToString(cam.getPosition()) + " heading: " + ofToString( cam.getHeadingDeg())
                           + " Lookat: " + ofToString( cam.getLookAtDir()) , 10, 10);
    }
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
            
        case 's':
            sortSigns();
            break;
            
        case 'h':
            cam.setDistance(2400);
            cam.setPosition(-300, 1720, -1650); // set camera looking at europe
            break;
            
    }
    
    if (key == 'l'){
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a folder with jpg image files");
        
        if (openFileResult.bSuccess){
            ofLogVerbose("User selected a folder");
            processOpenFileSelection(openFileResult);
            
        }else {
            ofLogVerbose("User hit cancel");
        }
    }
}

//--------------------------------------------------------------
sign::sign(){  // sign constructor
    
}

//--------------------------------------------------------------
sign::~sign(){    // sign destuctor
    
}

//--------------------------------------------------------------
void sign::load(string imagePath){
    // int imageScaleFactor = 10;
    cout << "loading: " << ofToString(imagePath) << endl;
    ofImageLoadSettings myImageLoadSettings;
    myImageLoadSettings.exifRotate = true;
    image.load(imagePath, myImageLoadSettings );
    // input routine here to resize images to target size if not already resized...
    //  image.resize(image.getWidth()/imageScaleFactor, image.getHeight()/imageScaleFactor);
    exifData =  getEXIF(imagePath);     // load XML from jpg
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
void sign::draw(int x, int y, int z, int scale ){
    int width, height;
     string signLabel;
    if (image.getWidth() > image.getHeight() ){ // determine portrait or landscape orientation
        width =  scale;
        height =  scale * 0.75;
    } else  {
        width =  scale * 0.75;
        height =  scale;
    }
    
    // signLabel = ofToString(exifData.GeoLocation.Latitude) + ", " + ofToString(exifData.GeoLocation.Longitude);
    // signLabel += " orientation: " + ofToString(exifData.Orientation);
    //  image.rotate90(1);
    // rotate to orientate as tangent to line to globe centre
    // rotate image perpendicluar to line to centre of globe
    ofVec2f v1(0, -1); // constant for heading angle and vector calculations
    ofVec2f XY(x,z);
    ofPushMatrix();
    
    float mapRotationXY =  v1.angle(XY);
    
   // ofTranslate(x-width/2.0,  y-height/2.0, z);
    ofTranslate(x, y, z);
    ofRotateYDeg(-mapRotationXY + 180);
    ofTranslate(-width/2.0,  -height/2.0, 0);
    signLabel = ofToString( exifData.DateTime ) ;
    image.draw( 0, 0, width, height) ;
    
    signFont.drawString(signLabel, width/2, height + 10);
    ofPopMatrix();
}

//--------------------------------------------------------------

ofVec3f ofApp::sphericalToCartesian( float lat, float lon, float radius ){
    ofVec3f result;
    // new quaternion example
    // three rotations, two to represent the latitude and lontitude of the city
    // a third so that it spins along with the spinning sphere
    ofQuaternion latRot, longRot, spinQuat;
    lat *= -1;        // inverse latitude.
    lon += 180;        // longitude offset to match geometry of the sphere.
    latRot.makeRotate(lat, 1, 0, 0);
    longRot.makeRotate(lon, 0, 1, 0);
    spinQuat.makeRotate(0, 0, 1, 0);
    
    //our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
    ofVec3f center = ofVec3f(0,0,globeRadius+signDist); // add distance above globe surface to draw to
    //multiplying a quat with another quat combines their rotations into one quat
    //multiplying a quat to a vector applies the quat's rotation to that vector
    //so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
    ofVec3f worldPoint = latRot * longRot * spinQuat * center;
    return worldPoint;
}

//--------------------------------------------------------------

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    
    ofFile file (openFileResult.getPath());
    ofFilePath dirPath;
    if (file.exists()){
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        if (fileExtension == "JPG") {         // We only want jpg images
            ofDirectory imageDirectory( dirPath.getEnclosingDirectory(file) );
            imageDirectory.listDir();
            imageDirectory.allowExt("jpg");
            imageDirectory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
            for (int i=0; i<imageDirectory.size(); i++){
                sign newSign;
                newSign.load(imageDirectory.getPath(i)) ;
                signsOfSurveillance.push_back(newSign);
            }
        }
    }
}

//--------------------------------------------------------------

void ofApp::sortSigns(){
    
    ofSort(signsOfSurveillance, ofApp::sortDescending);
    
}

//--------------------------------------------------------------

bool ofApp::sortDescending(const sign &i, const sign &j){
    
    return j.exifData.DateTime< i.exifData.DateTime; //sort the sign objects into order based upon datetime
    
}
