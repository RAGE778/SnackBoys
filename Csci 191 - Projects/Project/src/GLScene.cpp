#include "GLScene.h"
#include <GLLight.h>
#include <GLInputs.h>
#include <parallax.h>
#include <player.h>
#include <skyBox.h>
#include <windows.h>
#include <mmsystem.h>
#include <cmath>
#include <timer.h>

using namespace std;


timer* D = new timer();
timer* pCol = new timer();
timer* ballCollTimer = new timer();
float xx, yy;
int dirXX = 1, dirYY = 1;
float max_xx_yy;
float directionX = -2;
float directionY = 1;
float CurXpos = -3.5, CurYpos = -1.3 ; // Current x position of the ball, current y position of the ball,
float yex;
float ballSpeed = 0.0015;

float yVelocity = 0.0082;
float gravity = - 0.00003;


Model* modelTeapot = new Model();
Model* modelTeapot2 = new Model();

Inputs* KbMs = new Inputs();

parallax* plx = new parallax();
player* ply = new player();
player* ply2 = new player();
Model* wallA = new Model(); // left wall
Model* wallB = new Model(); // right wall
Model* wallC = new Model(); // top wall
Model* killBox = new Model();
Model* divide = new Model();
Model* hud = new Model();

//left side tiles
Model* tile1=new Model();
Model* tile2=new Model();
Model* tile3=new Model();
Model* tile4=new Model();
Model* tile5=new Model();
Model* tile6=new Model();
Model* tile7=new Model();

//middle tile
Model* tile8=new Model();

//right side tiles
Model* tile9=new Model();
Model* tile10=new Model();
Model* tile22=new Model();
Model* tile12=new Model();
Model* tile13=new Model();
Model* tile14=new Model();
Model* tile15=new Model();



Model* wallAHbawks = new Model(); // left wall
Model* wallBHbawks = new Model(); // right wall
Model* wallCHbawks = new Model(); // top wall
skyBox* sky = new skyBox;
Model* Ball = new Model(); // the ball
Model* BallHbawks = new Model();

textureLoader* tex0 = new textureLoader();
textureLoader* tex1 = new textureLoader();
textureLoader* tex2 = new textureLoader();
textureLoader* ballHBTex = new textureLoader();
textureLoader* ballHBTex2 = new textureLoader();
textureLoader* texc = new textureLoader();
textureLoader* texH = new textureLoader();

textureLoader* tileTex=new textureLoader();
textureLoader* tileTex2=new textureLoader();
textureLoader* tileTex3=new textureLoader();
textureLoader* tileTex4=new textureLoader();
textureLoader* tileTex5=new textureLoader();
textureLoader* tileTex6=new textureLoader();
textureLoader* tileTex7=new textureLoader();
textureLoader* tileTex8=new textureLoader();
textureLoader* tileTex9=new textureLoader();
textureLoader* tileTex10=new textureLoader();
textureLoader* tileTex11=new textureLoader();
textureLoader* tileTex12=new textureLoader();
textureLoader* tileTex13=new textureLoader();
textureLoader* tileTex14=new textureLoader();
textureLoader* tileTex15=new textureLoader();

GLScene::GLScene()
{
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
}

GLScene::~GLScene()
{
    //dtor
}

GLint GLScene::initGL()
{


    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    GLLight SetLight(GL_LIGHT0);
    GLLight Light(GL_LIGHT0);
    modelTeapot->modelInit("images/player/player0.png", true, tex0);
    modelTeapot2->modelInit("images/player/player0.png", true, tex0);
   // plx->parallaxInit("images/box/band-BG2.png");
    ply->playerInit();
    ply2->playerInit();
    sky->loadTextures();
    plx->parallaxInit("images/parallax/parallax_f.png");
    wallA->modelInit("images/box/vertical_hitbox.png", true, tex1);
    wallB->modelInit("images/box/vertical_hitbox.png", true, tex2);
    wallC->modelInit("images/box/nothing.png", true, texc);
    divide->modelInit("images/box/nothing.png", true, tex2);
    hud->modelInit("images/box/hud.png", true, texH);

    Ball->modelInit("images/box/ball.png", true, ballHBTex);
    BallHbawks->modelInit("images/box/hitbox.png",true, ballHBTex2);

    tile1->modelInit("images/platform/grass-block.png", true, tileTex);
    tile2->modelInit("images/platform/grass-block.png", true, tileTex2);
    tile3->modelInit("images/platform/grass-block.png", true, tileTex3);
    tile4->modelInit("images/platform/grass-block.png", true, tileTex4);
    tile5->modelInit("images/platform/grass-block.png", true, tileTex5);
    tile6->modelInit("images/platform/grass-block.png", true, tileTex6);
    tile7->modelInit("images/platform/grass-block.png", true, tileTex7);
    tile8->modelInit("images/platform/grass-block.png", true, tileTex8);
    tile9->modelInit("images/platform/grass-block.png", true, tileTex9);
    tile10->modelInit("images/platform/grass-block.png", true, tileTex10);
    tile22->modelInit("images/platform/grass-block.png", true, tileTex11);
    tile12->modelInit("images/platform/grass-block.png", true, tileTex12);
    tile13->modelInit("images/platform/grass-block.png", true, tileTex13);
    tile14->modelInit("images/platform/grass-block.png", true, tileTex14);
    tile15->modelInit("images/platform/grass-block.png", true, tileTex15);

    ply->PXpos = -2;
    ply2->PXpos = 2;

    ply->isPlayer = 1;
    ply2->isPlayer = 2;

    ply->T->start();
    ply->T2->start();
    ply2->T->start();
    ply2->T2->start();


    return true;
}



 static bool box_collision(Hbox rect1, Hbox rect2)
 {

 bool collisionX;
 bool collisionY;

collisionY = (((rect1.y-rect1.height) < (rect2.y + rect2.height) && (rect1.y+rect1.height) > (rect2.y - rect2.height))||((rect2.y-rect2.height) < (rect1.y + rect1.height) && (rect2.y+rect2.height) > (rect1.y - rect1.height)));
collisionX = (((rect1.x-rect1.width) < (rect2.x + rect2.width) && (rect1.x+rect1.width) > (rect2.x - rect2.width))||((rect2.x-rect2.width) < (rect1.x + rect1.width) && (rect2.x+rect2.width) > (rect1.x - rect1.width)));

    return collisionX && collisionY;
}


void tileChange(Model* b, Model* t,textureLoader* TX)
{
    if(box_collision(b->box, t->box ) && D->getTicks() >= 200)
    {
                D->reset();
                directionY =  1;
                t->health-=1;
                t->isalive();

                if (t->health == 2)
                    t->modelInit("images/platform/grass-block2.png", true, TX);
                if (t->health == 1)
                    t->modelInit("images/platform/grass-block3.png", true, TX);
                    return;
    }

}

static void update()
{
        CurXpos = CurXpos + 1.2*(directionX * ballSpeed);
        CurYpos = CurYpos + (directionY * ballSpeed);

    //-------------------------------------------------------------------------------------------------//
    //-------------------------------WALL COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    if (box_collision(Ball->box, wallB->box))
        directionX = -1;

    if (box_collision(Ball->box, wallA->box))
        directionX = 1;

    if (box_collision(Ball->box, wallC->box))
        directionY = -1;

    if (box_collision(Ball->box, killBox->box))
    {
        cout<<"kill box collision"<<endl;
       CurYpos=2;
       directionY=-1;

        if(directionX==-1)
        CurXpos+=2;

        if(directionX==1)
        CurXpos-=2;
    }

    //wall versus player collisions
    if(box_collision(ply->box,wallA->box))//player has hit the left wall
        ply->leftWC=true;//set to true so the player cannot move left
    else
        ply->leftWC=false;

    if(box_collision(ply->box,wallB->box))//player has hit the right wall
        ply->rightWC=true;//set to true so the player cannot move right
    else
        ply->rightWC=false;

    if(box_collision(ply2->box,wallA->box))//player has hit the left wall
        ply2->leftWC=true;//set to true so the player cannot move left
    else
        ply2->leftWC=false;

    if(box_collision(ply2->box,wallB->box))//player has hit the right wall
        ply2->rightWC=true;//set to true so the player cannot move right
    else
        ply2->rightWC=false;

    //---------------------------------------------------------------------------------------------------//
    //------------------------------- BALL VS PLAYER COLLISIONS -----------------------------------------//
    //---------------------------------------------------------------------------------------------------//

    //----------------------PLAYER 1 --------------------------------------//
    if (box_collision(Ball->box, ply->box) && ply->swinging == true && pCol->getTicks() >= 350)
    {
        if ((ply->playerDirection == "RIGHT" && Ball->Xpos >= ply->PXpos) || (ply->playerDirection == "LEFT" && Ball->Xpos <= ply->PXpos ))
        {
            pCol->reset();
            ballSpeed *= 1.2;
            if (ballSpeed > .0043)
            {
                ballSpeed = .0043;
            }
            if (ply->freezeTimer > 0)
            {
                ply->ballCollided = true;
                ply2->midCollision = true;

                ply->swingTimer->pause();
                ballCollTimer->reset();
                ballCollTimer->start();
            }

                //ballSpeed = ballSpeed + 0.002;
                //directionX =  -1;
                //directionY =  1;
                if(ply->swingDirection == "TOPRIGHT")
                {
                    directionX = 1;
                    directionY = 1;
                }
                else if(ply->swingDirection == "TOPLEFT")
                {
                    directionX = -1;
                    directionY = 1;
                }
                else if(ply->swingDirection == "BOTTOMLEFT")
                {
                    directionX = -1;
                    directionY = -1;
                }
                else if(ply->swingDirection == "BOTTOMRIGHT")
                {
                    directionX = 1;
                    directionY = -1;
                }
                else if(ply->swingDirection == "LEFT")
                {
                    directionX = -1;
                    directionY = 0;
                }
                else if(ply->swingDirection == "RIGHT")
                {
                    directionX = 1;
                    directionY = 0;
                }
        }

    }

        //---------------------- PLAYER 2 --------------------------------------//
    if (box_collision(Ball->box, ply2->box) && ply2->swinging == true && pCol->getTicks() >= 350)
    {
        if ((ply2->playerDirection == "RIGHT" && Ball->Xpos >= ply2->PXpos) || (ply2->playerDirection == "LEFT" && Ball->Xpos <= ply2->PXpos ))
        {
            pCol->reset();
            ballSpeed *= 1.2;
            if (ballSpeed > .0043)
            {
                ballSpeed = .0043;
            }
            if (ply->freezeTimer > 0)
            {
                ply2->ballCollided = true;
                ply->midCollision = true;

                ply2->swingTimer->pause();
                ballCollTimer->reset();
                ballCollTimer->start();
            }

                //ballSpeed = ballSpeed + 0.002;
                //directionX =  -1;
                //directionY =  1;
                if(ply2->swingDirection == "TOPRIGHT")
                {
                    directionX = 1;
                    directionY = 1;
                }
                else if(ply2->swingDirection == "TOPLEFT")
                {
                    directionX = -1;
                    directionY = 1;
                }
                else if(ply2->swingDirection == "BOTTOMLEFT")
                {
                    directionX = -1;
                    directionY = -1;
                }
                else if(ply2->swingDirection == "BOTTOMRIGHT")
                {
                    directionX = 1;
                    directionY = -1;
                }
                else if(ply2->swingDirection == "LEFT")
                {
                    directionX = -1;
                    directionY = 0;
                }
                else if(ply2->swingDirection == "RIGHT")
                {
                    directionX = 1;
                    directionY = 0;
                }
        }

    }


      //------------------------------------------------------------------------------------------------//
     //---------------------------- PLAYER JUMP & GROUND COLLISIONS -----------------------------------//
    //------------------------------------------------------------------------------------------------//

    //------------------------------- PLAYER 1 --------------------------------------//
    if(ply->jump>0)
        ply->PYpos+=ply->verticalVelocity;

               if(ply->PYpos<-1.181&&(box_collision(ply->pl_pltfrm_box,tile1->box)||box_collision(ply->pl_pltfrm_box,tile2->box)||box_collision(ply->pl_pltfrm_box,tile3->box)||box_collision(ply->pl_pltfrm_box,tile4->box)||
                    box_collision(ply->pl_pltfrm_box,tile5->box)||box_collision(ply->pl_pltfrm_box,tile6->box)||box_collision(ply->pl_pltfrm_box,tile7->box)||box_collision(ply->pl_pltfrm_box,tile8->box)||
                    box_collision(ply->pl_pltfrm_box,tile9->box)||box_collision(ply->pl_pltfrm_box,tile10->box)||box_collision(ply->pl_pltfrm_box,tile22->box)||box_collision(ply->pl_pltfrm_box,tile12->box)||
                    box_collision(ply->pl_pltfrm_box,tile13->box)||box_collision(ply->pl_pltfrm_box,tile14->box)||box_collision(ply->pl_pltfrm_box,tile15->box)))
                {
                    ply->PYpos=-1.181;
                    ply->jump=0;
               }

        else if(!(box_collision(ply->pl_pltfrm_box,tile1->box)||box_collision(ply->pl_pltfrm_box,tile2->box)||box_collision(ply->pl_pltfrm_box,tile3->box)||box_collision(ply->pl_pltfrm_box,tile4->box)||
                    box_collision(ply->pl_pltfrm_box,tile5->box)||box_collision(ply->pl_pltfrm_box,tile6->box)||box_collision(ply->pl_pltfrm_box,tile7->box)||box_collision(ply->pl_pltfrm_box,tile8->box)||
                    box_collision(ply->pl_pltfrm_box,tile9->box)||box_collision(ply->pl_pltfrm_box,tile10->box)||box_collision(ply->pl_pltfrm_box,tile22->box)||box_collision(ply->pl_pltfrm_box,tile12->box)||
                    box_collision(ply->pl_pltfrm_box,tile13->box)||box_collision(ply->pl_pltfrm_box,tile14->box)||box_collision(ply->pl_pltfrm_box,tile15->box)))
                {
                    if(ply->jump<=0)
                        ply->PYpos+=ply->verticalVelocity;
                    ply->verticalVelocity+=ply->playerGrav;
               }



    //------------------------------- PLAYER 2 --------------------------------------//
    if(ply2->jumpInitiated == false && ply2->onGround == false )
        ply2->PYpos -= 0.0015;

        if((box_collision(ply2->pl_pltfrm_box,tile1->box)||box_collision(ply2->pl_pltfrm_box,tile2->box)||box_collision(ply2->pl_pltfrm_box,tile3->box)||box_collision(ply2->pl_pltfrm_box,tile4->box)||
        box_collision(ply2->pl_pltfrm_box,tile5->box)||box_collision(ply2->pl_pltfrm_box,tile6->box)||box_collision(ply2->pl_pltfrm_box,tile7->box)||box_collision(ply2->pl_pltfrm_box,tile8->box)||
        box_collision(ply2->pl_pltfrm_box,tile9->box)||box_collision(ply2->pl_pltfrm_box,tile10->box)||box_collision(ply2->pl_pltfrm_box,tile22->box)||box_collision(ply2->pl_pltfrm_box,tile12->box)||
        box_collision(ply2->pl_pltfrm_box,tile13->box)||box_collision(ply2->pl_pltfrm_box,tile14->box)||box_collision(ply2->pl_pltfrm_box,tile15->box)))
            if (ply2->PYpos >= -1.19)
                ply2->onGround = true;
            else
                ply2->onGround = false;


      //-------------------------------------------------------------------------------------------------//
     //------------------------------- BALL VS TILE COLLISIONS -----------------------------------------//
    //-------------------------------------------------------------------------------------------------//


    tileChange(Ball, tile1,tileTex);
    tileChange(Ball, tile2,tileTex2);
    tileChange(Ball, tile3,tileTex3);
    tileChange(Ball, tile4,tileTex4);
    tileChange(Ball, tile5,tileTex5);
    tileChange(Ball, tile6,tileTex6);
    tileChange(Ball, tile7,tileTex7);
    tileChange(Ball, tile8,tileTex8);
    tileChange(Ball, tile9,tileTex9);
    tileChange(Ball, tile10,tileTex10);
    tileChange(Ball, tile22,tileTex11);
    tileChange(Ball, tile12,tileTex12);
    tileChange(Ball, tile13,tileTex13);
    tileChange(Ball, tile14,tileTex14);
    tileChange(Ball, tile15,tileTex15);

    Ball->Xpos = CurXpos;
    Ball->Ypos = CurYpos;
}

static void jumpUpdate(player* p)
{

}

void makeModel(Model* mod,textureLoader* texture,float xspot,float yspot,float ZeroX,float ZeroY,float OneX, float OneY, float TwoX, float TwoY, float ThreX, float ThreY, float w, float h)
{
       glPushMatrix();

        mod->Xpos=xspot;
        mod->Ypos=yspot;
        mod->box.x = mod->Xpos; // wallA->Xpos;
        mod->box.y = mod->Ypos;
        mod->verticies[0].x = ZeroX; // -0.15;
        mod->verticies[1].x = OneX; // 0.15;
        mod->verticies[2].x = TwoX; // 0.15;
        mod->verticies[3].x = ThreX; // -0.15;
        mod->verticies[0].y = ZeroY; // -0.15;
        mod->verticies[1].y = OneY; // -0.15;
        mod->verticies[2].y = TwoY; // 0.15;
        mod->verticies[3].y = ThreY; // 0.15;

        mod->box.height = h;
        mod->box.width = w;
        mod->drawModel(texture);
    glPopMatrix();
    return;
}

GLint GLScene::drawGLScene(bool pressed[256])
{
/*ply->freezeTimer = 10;
    if (ply->ballCollided == true || ply2->ballCollided == true)
    {
            max_xx_yy = 4;

        if (xx >= max_xx_yy)
        {
            dirXX = -1;
        }
        if (xx <= -max_xx_yy)
        {
            dirXX=1;
        }
        if (yy >= max_xx_yy)
        {
            dirYY = -1;
        }
        if (yy <= -max_xx_yy)
        {
            dirYY=1;
        }
            xx += dirXX*8;
            yy += dirYY*4;
        glViewport(xx,yy, screenWidth, screenHeight);
    }
    else
        glViewport(0,0, screenWidth, screenHeight);*/

        if (ballCollTimer->getTicks() >= ply->freezeTimer)
        {
            ballCollTimer->stop();
            ply->swingTimer->resume();
            ply->ballCollided = false;
            ply2->swingTimer->resume();
            ply2->ballCollided = false;
        }
      //-----------------------------------------------------------------------------------------------//
     //------------------------------------------ TIMERS ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
        D->start();
        pCol->start();
        ply->swingTimer->start();
        ply2->swingTimer->start();
        //ply->swingDuration->start();


      //-----------------------------------------------------------------------------------------------//
     //-------------------------------- SKYBOX CREATION ----------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
    glLoadIdentity();
    // Reset The Current Modelview Matrix
    glPushMatrix();
        glTranslated(0, 0, 1);
        glDisable(GL_LIGHTING);
        glScaled(10, 10, 10);
        sky->drawBox();
        glEnable(GL_LIGHTING);
    glPopMatrix();

      //-----------------------------------------------------------------------------------------------//
     //------------------------------- PARALLAX CREATION ---------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glPushMatrix();
        glScaled(2, 3.555, 1.0);
        plx->drawSquare(screenWidth, screenHeight);
    glPopMatrix();
    //plx->scroll(true,"up",0.005);

      //-------------------------------------------------------------------------------------------------//
     //------------------------------- PLAYER CREATION -------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    glPushMatrix();
        ply->actions();
        ply->box.x = ply->PXpos;
        ply->box.y = ply->PYpos;
        ply->pl_pltfrm_box.x = ply ->PXpos;
        ply->pl_pltfrm_box.y = ply -> PYpos;
        ply->pl_pltfrm_box.height = 0.6;
        ply->pl_pltfrm_box.width = 0.14;
        ply->box.height=0.5;
        ply->box.width=0.5;
        //ply->playerHBox.width = .0; // .3 is a perfect value
        //ply->playerHBox.height = .0; //.4 is a perfect value

        update();

            ply->drawplayer();
    glPopMatrix();



    glPushMatrix();

        ply2->actions();
        ply2->box.x = ply2->PXpos;
        ply2->box.y = ply2->PYpos;
        ply2->pl_pltfrm_box.x = ply2 ->PXpos;
        ply2->pl_pltfrm_box.y = ply2 -> PYpos;
        ply2->pl_pltfrm_box.height = 0.6;
        ply2->pl_pltfrm_box.width = 0.14;
        ply2->box.height=0.5;
        ply2->box.width=0.5;
        update();

            ply2->drawplayer();


        ply2->drawplayer();

    glPopMatrix();

      //-------------------------------------------------------------------------------------------------//
     //------------------------------- TILE CREATION ---------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//

    // model , texture, xpos,ypos, 0 X, 0 Y, 1 X, 1 Y, 2 X, 2 Y, 3 X, 3 Y, width, height
    if(tile1->health>0)
    makeModel(tile1,tileTex,-3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile2->health>0)
    makeModel(tile2,tileTex2,-2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile3->health>0)
    makeModel(tile3,tileTex3,-2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile4->health>0)
    makeModel(tile4,tileTex4,-1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile5->health>0)
    makeModel(tile5,tileTex5,-1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile6->health>0)
    makeModel(tile6,tileTex6,-0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile7->health>0)
    makeModel(tile7,tileTex7,-0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile8->health>0)
    makeModel(tile8,tileTex8, 0.00,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile9->health>0)
    makeModel(tile9,tileTex9, 0.49,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile10->health>0)
    makeModel(tile10,tileTex10, 0.98,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile22->health>0)
    makeModel(tile22,tileTex11, 1.47,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile12->health>0)
    makeModel(tile12,tileTex12, 1.96,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile13->health>0)
    makeModel(tile13,tileTex13, 2.45,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile14->health>0)
    makeModel(tile14,tileTex14, 2.94,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    if(tile15->health>0)
    makeModel(tile15,tileTex15, 3.43,-2.08,-0.25,-0.00,0.25,-0.00,0.25,0.40,-0.25,0.40,0.2200005,.3);

    //left wall
    makeModel(wallA,tex1,-4.7,0,-0.2,-2.0,0.2,-2.0,0.2,2.0,-0.2,2,1,88);

    //right wall
    makeModel(wallB,tex2,4.7,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,1,88);

    //top wall
    makeModel(wallC,texc,0,3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);

    //bottom wall
    makeModel(killBox,texc,0,-3.22,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,66,1);

    //dividing wall
    //makeModel(divide,tex2,0,0,-0.2,-2,0.2,-2,0.2,2,-0.2,2,.3,88);

    //ball creation
    //makeModel(Ball,ballHBTex,-0.5,-0.5,-0.15,-0.15,0.15,-0.15,0.15,0.15,-0.15,0.15,0.3,0.3);

      //-------------------------------------------------------------------------------------------------//
     //--------------------------------- TILE CREATION -------------------------------------------------//
    //-------------------------------------------------------------------------------------------------//
    glPushMatrix();
        Ball->box.height =  .2;
        Ball->box.width = .05;

        Ball->verticies[0].x = -0.15;
        Ball->verticies[1].x = 0.15;
        Ball->verticies[2].x = 0.15;
        Ball->verticies[3].x = -0.15;
        Ball->verticies[0].y = -0.15;
        Ball->verticies[1].y = -0.15;
        Ball->verticies[2].y = 0.15;
        Ball->verticies[3].y = 0.15;
        Ball->box.x = Ball ->Xpos;
        Ball->box.y = Ball ->Ypos;

        update();

        //Ball->UpdateHbox(Ball->Xpos, Ball->Ypos);
        Ball->drawModel(ballHBTex);
    glPopMatrix();

    glPushMatrix();
        hud->verticies[0].x = -1; //bottom left x
        hud->verticies[1].x = 1; //bottom right x
        hud->verticies[2].x = 1; //top right x
        hud->verticies[3].x = -1; //top left x
        hud->verticies[0].y = -1; //bottom left y
        hud->verticies[1].y = -1; //bottom right y
        hud->verticies[2].y = 1; //top right y
        hud->verticies[3].y = 1; // top left y
        hud->Xpos = -2.69;
        hud->Ypos = 1.15;
        //hud->Zoom = 0;
        hud->drawModel(texH); //made the z equal to 2 so the pillar is in front of the player
    glPopMatrix();
    KbMs->idle(pressed,ply,ply2);
    //cout << ply->PYpos << endl;
}
GLvoid GLScene::resizeGLScene(GLsizei width, GLsizei height)
{
    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspectRatio, 0.1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int GLScene::windMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,bool press[256])
{
    /*if(uMsg==WM_KEYDOWN)
    {
        KbMs->wParam = wParam;
        KbMs->keyEnv(plx, 0.005);
        KbMs->keyPressed(ply, ply2, modelTeapot, modelTeapot2, wallA, wallB, wallC,press);
    }
     if(uMsg==WM_KEYUP)
    {
        KbMs->wParam = wParam;
        KbMs->keyUp(ply, ply2, press);
    }*/
}
