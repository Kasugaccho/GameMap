#include <GameMap.hpp>
#include <RPG.hpp>
#include <ofMain.h>

void drawMap(const int32_t i_, const int32_t j_, const int32_t sx_, const int32_t sy_, const int32_t ex_, const int32_t ey_, const std::vector<std::vector<int>>& col_) {
	if (col_[i_][j_] == 1) ofSetColor(187, 187, 187);
	else ofSetColor(0, 0, 0);
	ofRect(sx_, sy_, ex_, ey_);
}

void crossKey(const int c_, float& x_, float& y_, const float v_) {
	switch (c_)
	{
	case 'w':
		y_ -= v_;
		break;
	case 's':
		y_ += v_;
		break;
	case 'a':
		x_ -= v_;
		break;
	case 'd':
		x_ += v_;
		break;
	}
}

class gameApp : public ofBaseApp {
public:
	float x = 11, y = 10;
	game::MapView mv;
	game::GameMap<int> col;

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
};

void gameApp::setup() {
	mv.reset(1024, 768, x, y, 20);
	col.reset(51, 31, 1);
	col.mazeDig_Make(1, 0);
	mv.setMapArraySize(col.data);
	mv.setMapArrayCeil();
}
void gameApp::update() {

}
void gameApp::draw() {
	mv.setMapView(x, y);
	mv.outputMapLoop(drawMap, col.data);
}
void gameApp::keyPressed(int key) {
	crossKey(key, x, y, 0.3f);
}

int main() {
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new gameApp());
}

//void keyPressed(int key);
//void keyReleased(int key);
//void mouseMoved(int x, int y);
//void mouseDragged(int x, int y, int button);
//void mousePressed(int x, int y, int button);
//void mouseReleased(int x, int y, int button);
//void mouseEntered(int x, int y);
//void mouseExited(int x, int y);
//void windowResized(int w, int h);
//void dragEvent(ofDragInfo dragInfo);
//void gotMessage(ofMessage msg);