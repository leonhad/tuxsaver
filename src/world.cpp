#include "world.hpp"
#include <math.h>

float absolute(float input)
{
  if (input<0) return 0-input;
  else return input;
}

World::World(TextureLoader *t) : Object("world")
{
#ifdef DEBUG
  cout << "constructing world..." << endl;
#endif
  waveHeight=0.3; //initial value

  //load configuration
  tuxSaverConf->setGroup("sea");
  if (tuxSaverConf->readEntry("waveSea","yes")=="yes") waveSea=true; else waveSea=false;
  if (tuxSaverConf->readEntry("seaTransparancy","yes")=="yes") seaTransparancy=true; else seaTransparancy=false;
  seaTransparancyLevel = tuxSaverConf->readEntry("seaTransparancyLevel","50").toInt();
  waveHeight= (tuxSaverConf->readEntry("waveHeight","30").toFloat())/100;

  tuxSaverConf->setGroup("island");
  if (tuxSaverConf->readEntry("waveIceberg","yes")=="yes") waveIceberg=true; else waveIceberg=false;

  //load textures
  tex = t;
  tex->addTexture("sky.png");
  tex->addTexture("water.png");

  pObj = gluNewQuadric();
  gluQuadricTexture(pObj,true);

  //init wave matrix
  float float_x, float_z;                     // loop counters. 
  for(float_x = 0.0f; float_x < 9.0f; float_x +=  0.2f )      {
    for(float_z = 0.0f; float_z < 9.0f; float_z += 0.2f)            {
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][0] = float_x - 4.4f;
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][1] = (float) (sin( ( (float_x*80)/360 ) * 3.14159 * 2 ));
      points[ (int) (float_x*5) ][ (int) (float_z*5) ][2] = float_z - 4.4f; 
    }
  }

  //the world is standard visible
  visible->state=0;
#ifdef DEBUG
  cout << "constructing world finished" << endl;
#endif
}

World::~World()
{
  delete tex;
  gluDeleteQuadric(pObj);   // Free the Quadric
}

void World::draw()
{
  glPushMatrix();
    if (visible->state!=1) drawSky();
  
    glPushMatrix();
    followobject->drawFollowObjects();
    glPopMatrix();
   
    glPushMatrix();
    drawIsland();
    glPopMatrix();
  
    glPushMatrix();
    if (visible->state!=1) drawSea(waveHeight,0.05);
    glPopMatrix();

  glPopMatrix();
}

void World::make()
{
#ifdef DEBUG
  cout << "making display list for world..." << endl;
#endif

  skydsplist=glGenLists(2);

  glNewList(skydsplist,GL_COMPILE);
  gluQuadricTexture(pObj,true);
  glPushMatrix();
  glColor4f(1.0,1.0,1.0,0);
  tex->bindTexture("sky.png");
  glDisable(GL_LIGHTING);
  //gluQuadricOrientation(pObj,GLU_INSIDE);
  glRotatef(-90,1.0f,0.0f,0.0f);
  glTranslatef(0,0,-28.5);
  //glTranslatef(0,0,0-28.5);
  gluCylinder(pObj,70,70,90,110,110);
  glPopMatrix();
  //gluQuadricOrientation(pObj,GLU_OUTSIDE);
  
  //TODO draw bottom of the sea and top of the sky

  //bottom of the sea
  tex->bindTexture("water.png");
  glEnable(GL_BLEND);
  glColor4f(1.0f,1.0f,1.0f,0.9f);
  glBegin(GL_QUADS);
      
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(80, -20, 80);
      
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-80, -20,80);
  
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-80, -20, -80);

  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(80, -20, -80);
  
  glEnd();
  glDisable(GL_BLEND);
  glEnable(GL_LIGHTING); 
  glEndList();    
  
  //Make static sea
  staticseadsplist=skydsplist+1;
  glNewList(staticseadsplist,GL_COMPILE);
 
  tex->bindTexture("water.png");
  glTranslatef(0,-1,0);
  glDisable(GL_LIGHTING);
  if (seaTransparancy)
    {
      glEnable(GL_BLEND);
      glColor4f(1.0f,1.0f,1.0f,(99-float(seaTransparancyLevel))/100);
    }
  glBegin(GL_QUADS);
  
  glTexCoord2f(0.0f,4.0f);
  glVertex3f(80, 0, 80);
  
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-80, 0,80);
  
  glTexCoord2f(4.0f, 0.0f);
  glVertex3f(-80, 0, -80);
  
  glTexCoord2f(4.0f, 4.0f);
  glVertex3f(80, 0, -80);
  
  glEnd();
  if (seaTransparancy)
    {
      glColor4f(1.0f,1.0f,1.0f,0.5f);
      glDisable(GL_BLEND);
    }
  glEnable(GL_LIGHTING);
  glEndList();
}


void World::drawSky()
{
  glPushMatrix();
  //call display list    
  glCallList(skydsplist);
  glPopMatrix();
}

//waveheight= height of the waves
//wavetime= time between two wave updates
void World::drawSea(float waveheigth,float wavetime)
{
  //WATER
  int x, z;
  float float_x, float_z, float_xb, float_zb;

  if (waveSea)
    {
      float s=20; //size of the sea;
      
      tex->bindTexture("water.png");
      glTranslatef(0,-1,0);
      glDisable(GL_LIGHTING);
      if (seaTransparancy)
	{
	  glEnable(GL_BLEND);
	  glColor4f(1.0f,1.0f,1.0f,(99-float(seaTransparancyLevel))/100);
	}
 
      glBegin(GL_QUADS);
      for (x=0; x<44; x++) {
	for (z=0; z<44; z++) {
	  float_x  = (float) (x)/11;
	  float_z  = (float) (z)/11;
	  float_xb = (float) (x+1)/11;
	  float_zb = (float) (z+1)/11;

	  glTexCoord2f(float_x, float_z);
	  glVertex3f(s* points[x][z][0], waveheigth*points[x][z][1],s*points[x][z][2] );

	  glTexCoord2f(float_x, float_zb );
	  glVertex3f(s*points[x][z+1][0], waveheigth*points[x][z+1][1], s*points[x][z+1][2] );

	  glTexCoord2f( float_xb, float_zb );
	  glVertex3f(s*points[x+1][z+1][0], waveheigth*points[x+1][z+1][1], s*points[x+1][z+1][2] );

	  glTexCoord2f( float_xb, float_z );
	  glVertex3f( s*points[x+1][z][0], waveheigth*points[x+1][z][1], s*points[x+1][z][2] );
	}
      }
      glEnd();

      if (seaTransparancy)
	{
	  glColor4f(1.0f,1.0f,1.0f,0.5f);
	  glDisable(GL_BLEND);
	}
      glEnable(GL_LIGHTING);
      //if the time between now and the latest wave is bigger than the time between the waves, we have to change the wavecoordinates to change the waves position.
      if (absolute(worldtime-latestwavetime)>wavetime)
	{
	  latestwavetime=worldtime;
	  
	  for (z = 0; z <45; z++) {
	    points[44][z][1] = points[0][z][1];
	  }
	  
	  for( x = 0; x < 44; x++ ) {
	    for( z = 0; z < 45; z++) {
	      points[x][z][1] = points[x+1][z][1];
	    }
	  }
	  
	  //update the height of the iceberg, this is caused by the waves
	  islandheight=(points[22][z][1])*waveHeight*0.6;
	}
    }
  //if wavesea=false, we don't wave the sea, just paint one quad
  else
    {
      glCallList(staticseadsplist);
    }
}

void World::drawIsland()
{
  glPushMatrix();
  updateMainCo();
 
  //TODO : use real sinus in stead of coordinats from matrix
  if (waveIceberg) island->move->execute(0,islandheight,0);
  island->draw();
  glPopMatrix();
}

void World::setIsland(Island* the_island)
{
  island=the_island;
}
