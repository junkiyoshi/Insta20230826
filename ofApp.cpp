#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 100, true, true, true);
	this->word = "123456";
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 30 < 20) {

		this->noise_step += ofMap(ofGetFrameNum() % 20, 0, 20, 0.3, 0.001);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	this->cam.setPosition(glm::vec3(0, 0, 800));
	ofRotateY(ofGetFrameNum());
	ofRotateX(215);

	int size = 65;
	for (int base_deg = 0; base_deg < 360; base_deg += 10) {

		ofPushMatrix();
		ofRotateY(base_deg);

		int deg_span = 60;
		int deg_start = (int)ofMap(ofNoise(cos(base_deg * DEG_TO_RAD) * 0.8, sin(base_deg * DEG_TO_RAD) * 0.8, this->noise_step), 0, 1, -360, 360);
		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span){

			ofPath chara_path = this->font.getCharacterAsPoints(this->word[(int)ofMap(deg, deg_start, deg_start + 360, 0, this->word.size())], true, false);
			vector<ofPolyline> outline = chara_path.getOutline();

			ofPushMatrix();
			ofTranslate(0, 0, -300);
			ofRotateX(deg);

			ofFill();
			ofSetColor(0);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 60);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofNoFill();
			ofSetColor(255);
			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				ofNextContour(true);

				auto vertices = outline[outline_index].getVertices();
				for (auto& vertex : vertices) {

					glm::vec3 location = vertex / 100 * size;
					location -= glm::vec3(size * 0.5, -size * 0.5, 60);

					ofVertex(location);
				}
			}
			ofEndShape(true);

			ofPopMatrix();
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}