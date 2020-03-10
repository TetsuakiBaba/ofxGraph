ofxGraph: a simple plotter for openframeworks
====
![Example screenshot](/ofxGraph.gif)
## Description
ofxGraph is a graph plotting addon for openframeworks.

1. single/multiple plot
2. Manual adjustable graph size and position
3. detailed plot data information
4. Adjustable buffer size
5. CSV file export with a save dialog
6. Automatic saving(position and size). except for ofxGui settings.
7. New: Added Bar Graph Mode. you can change graph mode to bar or plot.

## Usage
 1. Copy ofxGraph/Example/bin/data/ofxGraph directory to  your_OF_project_directory/bin/data
 2. Below is a minimal code to use ofxGraph.
```c++
void ofApp::setup(){

// ofxGraph Init
  graph.setup("sample");
  graph.setDx(1.0); // which means delta of time
  graph.setColor(ofColor::white);  // ofColor(255,255,255)
}
void ofApp::update(){
  // plot a random data on a each frame
  graph.add(ofRandom(-100,100));
}

void ofApp::draw(){
  ofBackground(50,50,50);
  graph.draw();
}
```

See Example for more detailed.

![Example screenshot](/screenshot.png)


## Install
ofxGui and ofxXmlSettings are required.

## Licence
[MIT](https://opensource.org/licenses/MIT)

## Author
[TetsuakiBaba](https://github.com/TetsuakiBaba)
