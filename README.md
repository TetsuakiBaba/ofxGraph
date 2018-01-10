ofxGraph
====

## Description
ofxGraph is a simple addon library for openframeworks.

1. Adjustable graph size and position manually
2. shows graph
3. shows detailed plot data information
4. Flexible buffer size
5. CSV file export

## Usage
```c++
void ofApp::setup(){

    // ofxGraph Init
    graph.setup(100, 100, 600, 300); // x, y, w, h
    graph.setName("sample");
    graph.setDx(1.0); // which means delta of time
    graph.color.set(255,255,255); // white

}
void ofApp::update(){
    graph.add(ofRandom(-100,100));
}

void ofApp::draw(){
    ofBackground(50,50,50);
    graph.draw();
}
```
See Example for more detailed.

![Example screenshot](/snapshot.png)
<https://www.youtube.com/watch?v=bwaJbC1F6sI&feature=youtu.be>

## Install
ofxGui and ofxXmlSettings are required.

## Licence
[MIT](https://opensource.org/licenses/MIT)

## Author
[TetsuakiBaba](https://github.com/TetsuakiBaba)
