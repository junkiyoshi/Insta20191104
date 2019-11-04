#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(150, 3);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh_list.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		ofMesh mesh;

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.01, avg.y * 0.01, avg.z * 0.01, ofGetFrameNum() * 0.003);

		mesh.addVertex(triangle.getVertex(0));
		mesh.addVertex(triangle.getVertex(1));
		mesh.addVertex(triangle.getVertex(2));

		mesh.addIndex(0);
		mesh.addIndex(1);
		mesh.addIndex(2);

		auto noise_radius = 150;
		if (noise_value > 0.5) {

			noise_radius += ofMap(noise_value, 0.5, 1, 0, 80);

			mesh.addVertex(glm::normalize(avg) * noise_radius);

			mesh.addIndex(3);
			mesh.addIndex(0);
			mesh.addIndex(1);

			mesh.addIndex(3);
			mesh.addIndex(1);
			mesh.addIndex(2);

			mesh.addIndex(3);
			mesh.addIndex(2);
			mesh.addIndex(0);
		}

		this->mesh_list.push_back(mesh);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.25);
	ofRotateX(ofGetFrameNum() * 0.15);

	for (auto& mesh : this->mesh_list) {

		ofSetColor(39);
		mesh.drawFaces();

		ofSetColor(239);
		mesh.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}