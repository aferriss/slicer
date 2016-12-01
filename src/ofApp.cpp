#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    file = "images/turbineL.jpg";
    img.load(file);
    img2.load("images/carl.jpg");
    
    w = img.getWidth();
    h = img.getHeight();
    
    img2.resize(w, h);
    
    ofSetWindowShape(w/2, h/2);
    ofSetVerticalSync(false);
    
    shader.load("base");
    
    fbo.allocate(w, h,GL_RGBA,  8);
    post.allocate(w, h);
    
    genXYPositions();
    
    save = false;
    doWidth = true;
    copyToImg = false;
    justRendered = false;
    
    
    jenn.load("images/faces/jenn.jpg");
    fang.load("images/faces/fang.jpg");
    carl.load("images/faces/carl.jpg");
    kathy.load("images/faces/kathy.jpg");
    emma.load("images/faces/emma.jpg");
    
    scientists.push_back(jenn);
    scientists.push_back(fang);
    scientists.push_back(carl);
    scientists.push_back(kathy);
    scientists.push_back(emma);
    
    for(int i =0; i<scientists.size(); i++){
        scientists[i].resize(w, h);
    }
    
    fbo.begin();
        ofClear(0,255);
    fbo.end();
    
    post.begin();
    ofClear(0,255);
    post.end();
    
    vid.load("clouds.mp4");
    vid.play();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vid.update();
    if(save){
        ofPixels savePix;
        post.readToPixels(savePix);
        ofSaveImage(savePix, "saved/"+ofGetTimestampString()+".png");
        save = false;
    }
    
    if(copyToImg){
        ofPixels imgPix;
        post.readToPixels(imgPix);
        img.setFromPixels(imgPix);
//        for(int i = 0; i<scientists.size(); i++){
//            scientists[i].setFromPixels(imgPix);
//        }
        justRendered = true;
        copyToImg = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//    fbo.begin();
//    
////    img.draw(0,0);
//    if(!justRendered){
//        if(doWidth){
//            for(int i = 0; i<xPositions.size()-1; i++){
//                int xWidth = xPositions[i+1] - xPositions[i];
////                scientists[(int)ofRandom(scientists.size())].drawSubsection(xPositions[i], yPositions[i], xWidth, h, xPositions[i], 0 );
//                    img.drawSubsection(xPositions[i], yPositions[i], xWidth, h, xPositions[i], 0 );
//                
//            }
//        }
//        else if(!doWidth){
//            for(int i = 0; i<yPositions.size()-1; i++){
//                int yHeight = yPositions[i+1] - yPositions[i];
//                img.drawSubsection(xPositions[i], yPositions[i], w, yHeight, 0, yPositions[i] );
//
////                    scientists[(int)ofRandom(scientists.size())].drawSubsection(xPositions[i], yPositions[i], w, yHeight, 0, yPositions[i] );
//               
//            }
//        }
//    }
//    fbo.end();
//    
//    fbo.draw(0,0, w/2, h/2);
    
    
     
    
    fbo.begin();
    if(ofGetKeyPressed(' ')){
        ofClear(0,255);
    }
    float x = floor(ofRandom(3)/3*w);
    float y = floor(ofRandom(3)/3*h);
    cout<<ofToString(x)<<endl;
    float tileSize = 100;//ofRandom(60);
//    cam.begin();
//        for(int j = -10; j <= 10 ; j++){
//            ofDrawLine(j*10, -100, j*10, 100);
//            ofDrawLine(-100, j*10, 100, j*10);
//            ofDrawLine(-100, 0, j*10, 100, 0, j*10);
//            ofDrawLine(0, -100, j*10, 0, 100, j*10);
//            ofDrawLine(j*10, 0, -100, j*10, 0, 100);
//            ofDrawLine(0, j*10, -100, 0, j*10, 100);
//        }
    
//        img.drawSubsection(x -w/2,y - h/2, tileSize, tileSize, x ,y );
    img.draw(0,0,w,h);
//    cam.end();
    fbo.end();
    
    
//    ofEnableBlendMode(OF_BLENDMODE_SCREEN);
    post.begin();
    cam.begin();
    shader.begin();
        shader.setUniformTexture("tex0", fbo.getTexture(), 0);
//    float which1 =
    shader.setUniform3f("which", 1, 1, 1);
//    shader.setUniform3f("which", (ofGetFrameNum() % 15) == 0 ? 0.0 : 1.0, (ofGetFrameNum()+1) % 15 == 0 ? 0.0 : 1.0, (ofGetFrameNum()+2) % 15 == 0 ? 0.0 : 1.0);
//        fbo.draw(0,0);
        fbo.getTexture().drawSubsection(x-w/2,y-h/2, tileSize, tileSize, x ,y );
    shader.end();
    cam.end();
    post.end();
    ofDisableBlendMode();
    post.draw(0,0, w/2, h/2);
    
    
//    cout<<ofToString(ofSignedNoise(ofGetFrameNum()*0.001))<<endl;
}
//--------------------------------------------------------------
void ofApp::genXYPositions(){
    int sumY = 0;
    int sumX = 0;
    int extraMin = 0;
    int extraMax = 0;
    int extraThresh = 19;
    
    int barMin = w*.01;
    int barMax = w*.02;
    
    int offSet = w*.04;
    yPositions.clear();
    xPositions.clear();
    justRendered = false;
    
    if(doWidth){
        for(int i = 0; i<w; i++){
            int r = ofRandom(10);
            int extra = 0;
            if(r>extraThresh){
                extra = ofRandom(extraMin,extraMax)*(int)ofRandom(-2, 2);
            }
            int randX = (int)ofRandom(barMin,barMax)+extra;
            int randY = (int)ofRandom(-offSet,offSet);
            sumX += randX;
            
            if( sumX  < w ){
                xPositions.push_back(sumX);
                yPositions.push_back(randY+extra);
            }
        }
    } else if (!doWidth){
        for(int i = 0; i<h; i++){
            int r = ofRandom(10);
            int extra = 0;
            if(r>extraThresh){
                extra = ofRandom(extraMin,extraMax)*(int)ofRandom(-2, 2);
            }
            int randY = (int)ofRandom(barMin,barMax)+extra;
            int randX = (int)ofRandom(-offSet,offSet);
            sumY += randY;
            
            if( sumY  < h){
                yPositions.push_back(sumY);
                xPositions.push_back(randX+extra);
            }
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        genXYPositions();
    }
    if(key == 's'){
        save = true;
    }
    if(key == 'x'){
        doWidth = !doWidth;
        genXYPositions();
    }
    if(key == 'r'){
        copyToImg = true;
    }
    
    if(key == 'q'){
        img.load(file);
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
