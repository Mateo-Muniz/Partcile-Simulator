#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;
	currentSize = 1;
	currentSpeed = 1;
	isRecording = false;
	Playback = false;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	//these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		p[i].reset();
		p[i].setScale(p[i].getScale()*currentSize);
		p[i].setVelocity(p[i].getVelocity() * currentSpeed);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	float timer = (60 * 5);
	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].update();
	}

	//lets add a bit of movement to the attract points
	for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
	{
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}
	if (Playback == true)
	{
		if(timer < 300)
		{
			timer++;
		}
		if (timer == 300)
		{
			
			
			timer = 1;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(90, 10, 100), ofColor(80, 70, 150));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	ofSetColor(230);
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);

	if (isRecording == true)
	{
		ofSetColor(255,0,0);
		ofDrawCircle(250,20,10);
		
	}
	if (currentMode == PARTICLE_MODE_EASTER_EGG)
	{
		ofSetColor(236, 152, 63);
		ofDrawCircle(500, 500, 250);
		ofSetColor(0, 0, 0);
		ofDrawCircle(600, 400, 20);
		ofSetColor(0, 0, 0);
		ofDrawCircle(400, 400, 20);
		ofSetColor(0, 0, 0);
		ofDrawTriangle(510, 490, 490, 500, 510, 510);
		ofSetColor(0, 0, 0);
		ofDrawRectangle(450, 650, 100, 10);

	}
	
		

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '1')
	{
		
		if (isRecording == true)
		{
			inputs += "1";
		}	
		else
		{
			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
		}
	}
	if (key == '2')
	{
		if(isRecording == true)
		{
			inputs += '2';
		}
		else
		{
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
		}
	}
	if (key == '3')
	{
		if(isRecording)
		{
			inputs +='3';
		}
		else
		{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:";
		}
	}
	if (key == '4')
	{
		if(isRecording)
		{
			inputs += '4';
		}
		else
		{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
		}
	}

	if (key == ' ')
	{
		if (isRecording)
		{
			inputs += ' ';
		}
		else{
		resetParticles();
		}
	}
	if (key == 'i' || key == 'I')
	{
		if(isRecording)
		{
			inputs += 'i';
		}
		else
		{
		currentSize *= 3;
		resetParticles();
		}
	}
	if (key == 'd' || key == 'D')
	{
		if(isRecording)
		{
			inputs += 'd';
		}
		else
		{
			currentSize /= 3;
			resetParticles();
			if (currentSize <=0)
			{
				currentModeStr = "You have Excecuted Order 66";
				resetParticles();
			}
			else
			{
				resetParticles();
			}
		}
	}
	if (key == 'f'|| key == 'F')
	{
		if(isRecording)
		{
			inputs += 'f';
		}
		else
		{
		currentSpeed *= 4;
		currentModeStr = "Thank You For paying your respects!";
		resetParticles();
		}
	}
	if (key == 's'|| key == 'S')
	{
		if(isRecording)
		{
			inputs += 's';
		}
		else{
		currentSpeed /= 4;
		resetParticles();
		}
	}
	if (key == 'a'|| key == 'A')
	{
		if(isRecording)
		{
			inputs += 'a';
		}
		else
		{
		currentMode = PARTICLE_MODE_PAUSE;
		currentModeStr = "The Particles are paused";
		}
	}
	if (key == 'r'|| key == 'R')
	{
		isRecording = true;
		currentModeStr = "The Program is now Recording" "\nPress t to finish recording";
		
	}
	if (key == 't'|| key == 'T')
	{
	
		isRecording = false;
		currentModeStr = "Finished Recording";
		
	}
	if (key == 'p'|| key == 'P')
	{
		Playback  = true;
		currentModeStr = "Playing back: " + inputs + "\nPress 'c' to clear";
			

	}
	if (key == 'c'|| key == 'C')
	{
		Playback = false;
		currentSize = 1;
		currentSpeed = 1;
		inputs = " ";
		currentModeStr = "Cleared Screen";
		currentMode =  PARTICLE_MODE_ATTRACT;
		resetParticles();
	}
	if (key == 'q'|| key == 'Q')
	{
		currentMode = PARTICLE_MODE_EASTER_EGG;
		currentSize /= 1000;
		currentModeStr = "Well, this is awkward, why are you pressing random keys?" 
		"\nWell no matter as long if you dont press the '*', then you will be fine";
		resetParticles();
	}
	if (key == '*') //This is for the person reviewing this code... Im sorry that i did this XD. It was just a funny joke XD
	//Remember to drink plenty of water as well :v
	{
		currentMode = PARTICLE_MODE_WTF;
		"launch game Nintendo Land has a minigame based on the series called 'Metroid Blast'";
	}
	
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}