ofxGraph
====

## Description
ofxGraph is a simple addon library for openframeworks.

1. Adjustable graph size and position manually
2. shows graph
3. shows detailed plot data information
4. Flexible buffer size
5. CSV file export
6. Automatic saving(position and size). except for ofxGui settings.

## Usage
```c++
void ofApp::setup(){

// ofxGraph Init
  graph.setup();
  graph.setName("sample");     // it automatically loads setting file, (sample.xml)
  graph.setDx(1.0); // which means delta of time
  graph.setColor(ofColor::white);  // ofColor(255,255,255)
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

![Example of FFT and Spectrum](/ofxGraph_FFT_Example.png)
<https://www.youtube.com/watch?v=4i5nDxlcuS0&feature=youtu.be>
## Install
ofxGui and ofxXmlSettings are required.

## Licence
[MIT](https://opensource.org/licenses/MIT)

## Author
[TetsuakiBaba](https://github.com/TetsuakiBaba)
