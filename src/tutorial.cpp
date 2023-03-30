#include "tutorial.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yspng.h"

void Tutorial::drawTargetWord(char letters[]){
	glRasterPos2i(100, 32);
	YsGlDrawFontBitmap16x24(letters);
}

void Tutorial::drawResult(bool result){
	if(result == 1){
		glRasterPos2i(400, 32);
		YsGlDrawFontBitmap16x24("Correct!");
	}else{
		glRasterPos2i(400, 32);
		YsGlDrawFontBitmap16x24("Incorrect Spelling");
		glRasterPos2i(410, 62);
		YsGlDrawFontBitmap16x24("Try Again");
		std::cout << result;
	}
}

void Tutorial::PlayInstructions(void){

	for(int i = 0; i < 1600; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glColor3f(1,1,1);
		glRasterPos2i(0, 599);
		glDrawPixels(bkgd.wid,bkgd.hei,GL_RGBA,GL_UNSIGNED_BYTE,bkgd.rgba);

		if(i < 400){
			glRasterPos2i(82, 112);
			YsGlDrawFontBitmap16x24("Welcome to Alphabet Astronauts!");
			glRasterPos2i(82, 142);
			YsGlDrawFontBitmap16x24("Our games will test your typing skills");
		} else if(i < 1000){
			glRasterPos2i(82, 112);
			YsGlDrawFontBitmap16x24("In the following tutorial...");
			glRasterPos2i(82, 142);
			YsGlDrawFontBitmap16x24("A target word will appear on screen");
			glRasterPos2i(82, 172);
			YsGlDrawFontBitmap16x24("Simply type that word, press enter to submit");
		}else if(i < 1200){
			glRasterPos2i(82, 112);
			YsGlDrawFontBitmap16x24("Note: words ARE case sensitive");
		}else if(i < 1400){
			glRasterPos2i(22, 112);
			YsGlDrawFontBitmap16x24("Press ESC at any time to return to the Main Menu");
		}else{
			glRasterPos2i(82, 112);
			YsGlDrawFontBitmap16x24("Enjoy the tutorial");
		}

		FsSwapBuffers();
		FsSleep(10);
	}
	state = 1;
}

void Tutorial::ReturnToMenu(void){
	for(int i = 0; i < 100; i++){
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glColor3f(1,1,1);
		glRasterPos2i(0, 599);
		glDrawPixels(bkgd.wid,bkgd.hei,GL_RGBA,GL_UNSIGNED_BYTE,bkgd.rgba);

		glRasterPos2i(82, 112);
		YsGlDrawFontBitmap16x24("Now returning to the Main Menu");

		FsSwapBuffers();
		FsSleep(10);
	}
}

void Tutorial::Run(void){
	Initialize();
	while(true != terminate){
		RunOneStep();
		Draw();
		FsSleep(10);
	}
}

void Tutorial::Initialize(void){
	terminate = false;
	state = 0;
	textInput.BeginInput();
	bkgd.Decode("../media/background.png");
	bkgd.Flip();
}

void Tutorial::RunOneStep(void){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(1,1,1);
	glRasterPos2i(0, 599);
	glDrawPixels(bkgd.wid,bkgd.hei,GL_RGBA,GL_UNSIGNED_BYTE,bkgd.rgba);
	if(state == 0){
		PlayInstructions();
	}
	

	FsPollDevice();
	auto key=FsInkey();
	auto c=FsInkeyChar();

	std::string targetWord = wordBank[wordCount];
	auto len = targetWord.size();
	char letters[256];
	strcpy(letters, targetWord.c_str());

	inputStr = textInput.str.GetPointer();

	textInput.RunOneStep(key,c);
	drawTargetWord(letters);
	textInput.Draw();

	if(FSKEY_ENTER == key){
		if(inputStr.GetPointer() == targetWord){
			wordCount++;
			glColor3f(0,1,0);
			drawResult(true);

			auto completeTime = FsPassedTime();
			std::cout << "Completion time: " << completeTime*0.001 << " seconds." << std::endl;

			FsSwapBuffers();
			FsSleep(1000);
		}else{
			glColor3f(1,0,0);
			drawResult(false);

			FsSwapBuffers();
			FsSleep(2000);
		}
		textInput.str.CleanUp();
		inputStr.CleanUp();
	}
	if(wordCount >= sizeof(wordBank)/sizeof(wordBank[0]) || FsGetKeyState(FSKEY_ESC)) {
		ReturnToMenu();
		terminate = true;
	}
}

void Tutorial::Draw(void){

	FsSwapBuffers();
}
