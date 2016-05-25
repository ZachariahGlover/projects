/*
CSC D18 - RayTracer code.

Written Dec. 9 2010 - Jan 20, 2011 by F. J. Estrada
Freely distributable for adacemic purposes only.

Uses Tom F. El-Maraghi's code for computing inverse
matrices. You will need to compile together with
svdDynamic.c

You need to understand the code provided in
this file, the corresponding header file, and the
utils.c and utils.h files. Do not worry about
svdDynamic.c, we need it only to compute
inverse matrices.

You only need to modify or add code in sections
clearly marked "TO DO"

Last updated: Aug. 12, 2014   - F.J.E.
*/

#include <pthread.h>
#include "utils.h"	// <-- This includes RayTracer.h

void buildScene(int sceneSelect, struct object3D **object_list, struct pointLS **light_list, struct textureNode **texture_list) {
	// Sets up all objects in the scene. This involves creating each object,
	// defining the transformations needed to shape and position it as
	// desired, specifying the reflectance properties (albedos and colours)
	// and setting up textures where needed.
	// Light sources must be defined, positioned, and their colour defined.
	// All objects must be inserted in the object_list. All light sources
	// must be inserted in the light_list.
	//
	// To create hierarchical objects:
	//    You must keep track of transformations carried out by parent objects
	//    as you move through the hierarchy. Declare and manipulate your own
	//    transformation matrices (use the provided functions in utils.c to
	//    compound transformations on these matrices). When declaring a new
	//    object within the hierarchy
	//    - Initialize the object
	//    - Apply any object-level transforms to shape/rotate/resize/move
	//      the object using regular object transformation functions
	//    - Apply the transformations passed on from the parent object
	//      by pre-multiplying the matrix containing the parent's transforms
	//      with the object's own transformation matrix.
	//    - Compute and store the object's inverse transform as usual.
	//
	// NOTE: After setting up the transformations for each object, don't
	//       forget to set up the inverse transform matrix!

  	struct object3D *o;
  	struct pointLS *l;

  	//Objects
  	//ra, rd, rs, rg, R, G, B, alpha, r_index, and shinyness

  	if (sceneSelect == 0) {

  		//Final scene//

  		addPlanarLight(1.25, 0.3, PI/2, 0.0, PI/3, -2.95, 5.89, 9.73, 1.0, 1.0, 1.0, object_list, light_list, texture_list, "textures//light.ppm");
  		addPlanarLight(1.25, 0.3, PI/2, 0.0, PI/3, 2.9, 5.89, 6.25, 1.0, 1.0, 1.0, object_list, light_list, texture_list, "textures//light.ppm");

  		//mirror 1
  		o=newPlane(0.0, 0.1, 0.8, 1.0, 0.8, 0.8, 0.8, 1, 1, 8);
		Scale(o, 3.3, 2.2, 1.0);
		RotateY(o, -PI/3);
		Translate(o, -6.95, 0.95, 12.0);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//mirror.ppm", 1, texture_list);
		insertObject(o, object_list);

  		//background texture plane 1
  		o=newPlane(0.65, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1, 1, 1);
		Scale(o, 4.2, 7.0, 1.0);
		RotateY(o, -PI/3);
		Translate(o, -7.8, 2.2, 10.8);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//space.ppm", 1, texture_list);
		insertObject(o, object_list);

		//background texture plane 2
  		o=newPlane(0.65, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1, 1, 1);
		Scale(o, 3.3, 3.3, 1.0);
		RotateX(o, -PI/1.6);
		RotateY(o, -PI/5);
		Translate(o, -6.95, -6.3, 8.0);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//cat.ppm", 1, texture_list);
		insertObject(o, object_list);

		//floor
		o=newPlane(0.3, 0.8, 0.3, 0.2, 1.0, 1.0, 1.0, 1, 1, 4);
		Scale(o, 5.0, 8.09017, 1.0);
		RotateZ(o, PI/3);
		RotateX(o, PI/2);
		Translate(o, 0.0, -4.0, 8.0);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//tile1024.ppm", 1, texture_list);
		insertObject(o, object_list);

		//back wall
		o=newPlane(0.3, 0.8, 0.25, 0.1, 1.0, 1.0, 1.0, 1, 1, 4);
		Scale(o, 8.09017, 5.0, 1.0);
		RotateY(o, PI/6);
		Translate(o, 2.55, 0.95, 12.4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//tile1024.ppm", 1, texture_list);
		insertObject(o, object_list);

		//left wall
		o=newPlane(0.3, 0.8, 0.25, 0.1, 1.0, 1.0, 1.0, 1, 1, 4);
		Scale(o, 5.0, 5.0, 1.0);
		RotateY(o, -PI/3);
		Translate(o, -6.96, 0.95, 12.02);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//tile1024.ppm", 1, texture_list);
		insertObject(o, object_list);

		//right wall
		o=newPlane(0.3, 0.8, 0.25, 0.1, 1.0, 1.0, 1.0, 1, 1, 4);
		Scale(o, 5.0, 5.0, 1.0);
		RotateY(o, (2 * PI)/3);
		Translate(o, 7.5, 0.95, 5.0);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//tile1024.ppm", 1, texture_list);
		insertObject(o, object_list);

		//ceiling
		o=newPlane(0.3, 0.8, 0.4, 0.0, 1.0, 1.0, 1.0, 1, 1, 1);
		Scale(o, 5.0, 8.09017, 1.0);
		RotateZ(o, PI/3);
		RotateX(o, PI/2);
		Translate(o, 0.0, 5.9, 8.0);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//ceiling.ppm", 1, texture_list);
		insertObject(o, object_list);

		//chair bounding box
		struct object3D *b;
		b=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		b->isBounding = 1;
		Scale(b, 1.2, 2.4, 1.2);							
		Translate(b, -6.0, -2.0, 6.0);
		RotateY(b, PI/4);
		invert(&b->T[0][0], &b->Tinv[0][0]);
		insertObject(b, object_list);

		//chair pieces
		//l1
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 0.65, 0.1);
		Translate(o, -5.48, -3.35, 5.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//0wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//l2
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 0.65, 0.1);									
		Translate(o, -6.82, -3.35, 5.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//1wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//l3
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 1.85, 0.1);									
		Translate(o, -5.48, -2.3, 6.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//2wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//l4
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 1.85, 0.1);									
		Translate(o, -6.82, -2.3, 6.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//1wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//Seat
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.73, 0.08, 0.55);							
		Translate(o, -6.0, -2.7, 5.75);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//wood256.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//tr1
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.5, 0.08, 0.08);									
		Translate(o, -6.15, -1.95, 6.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//1wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//tr2
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.5, 0.08, 0.08);									
		Translate(o, -6.15, -1.25, 6.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//2wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//tr3
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.5, 0.08, 0.08);									
		Translate(o, -6.15, -0.55, 6.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//0wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//br1
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.55, 0.06, 0.1);									
		Translate(o, -6.15, -3.2, 5.6);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//0wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//br2
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 0.06, 0.5);									
		Translate(o, -5.5, -3.2, 6.08);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//0wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

		//br3
		o=newBox(0.3, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
		Scale(o, 0.1, 0.06, 0.5);									
		Translate(o, -6.8, -3.2, 6.08);
		RotateY(o, PI/4);
		invert(&o->T[0][0], &o->Tinv[0][0]);
		loadTexture(o, "textures//0wood128.ppm", 1, texture_list);
		insertBoundedObject(b, o, &b->b_next);

  	} else if (sceneSelect == 1) {

  		struct point3D p;

  		p.px = 0.0;
  		p.py = 15.0;
  		p.pz = -3.0;
  		p.pw = 1.0;
  		l = newPLS(&p,1.0,1.0,1.0);
		insertPLS(l,light_list);

  		//Simple scene
  		o=newPlane(.3,.6,.6,.05,.9,.35,.95,1,1,2);
		Scale(o,11,11,11);
		RotateZ(o,PI/4);
		RotateX(o,PI/2);
		Translate(o,0,-4,5);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(.35,.25,.5,.3,1.0,.05,.05,1,1,3);
		Scale(o,1.0,1.0,1.0);
		Translate(o,0.0,-1.0,4.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

  	} else if (sceneSelect == 2) {

  		struct point3D p;
  		p.px = 0.0;
  		p.py = 15.0;
  		p.pz = -3.0;
  		p.pw = 1.0;
  		l = newPLS(&p,1.0,1.0,1.0);
		insertPLS(l,light_list);

		//Refraction scene
		o=newBox(.35,.25,.5,.3,1.0,.05,.05,1,1,3);
		Scale(o,5.0,0.2,0.2);									
		Translate(o,0.0,0.0,7.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newBox(.35,.25,.5,.3,.05,1.0,.05,1,1,3);
		Scale(o,5.0,0.2,0.2);									
		Translate(o,0.0,0.6,7.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newBox(.35,.25,.5,.3,.05,.05,1.0,1,1,3);
		Scale(o,5.0,0.2,0.2);									
		Translate(o,0.0,1.2,7.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);	

		o=newSphere(0.25, 0.3, 0.4, 0.2, 0.8, 0.8, 0.8, 0.1, 0.5, 6);
		Scale(o,0.65,0.65,0.65);
		Translate(o,-2.3,0.3,5.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(0.25, 0.3, 0.4, 0.2, 0.8, 0.8, 0.8, 0.1, 1.0, 6);
		Scale(o,0.65,0.65,0.65);
		Translate(o,0.0,0.3,5.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(0.25, 0.3, 0.4, 0.2, 0.8, 0.8, 0.8, 0.1, 1.5, 6);
		Scale(o,0.65,0.65,0.65);
		Translate(o,2.3,0.3,5.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

  	} else if (sceneSelect == 3) {

  		struct point3D p;
  		p.px = 0.0;
  		p.py = 15.0;
  		p.pz = -3.0;
  		p.pw = 1.0;
  		l = newPLS(&p,1.0,1.0,1.0);
		insertPLS(l,light_list);

  		//Depth of field scene
  		o=newPlane(.3,.6,.6,.05,.9,.35,.95,1,1,2);
		Scale(o,11,11,11);
		RotateZ(o,PI/4);
		RotateX(o,PI/2);
		Translate(o,0,-4,5);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(.35,.25,.5,.3,1.0,.05,.05,1,1,3);
		Scale(o,0.8,0.8,0.8);
		Translate(o,-2.5,-1.0,2.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(.35,.25,.5,.3,1.0,.05,.05,1,1,3);
		Scale(o,0.8,0.8,0.8);
		Translate(o,0.0,-1.0,4.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

		o=newSphere(.35,.25,.5,.3,1.0,.05,.05,1,1,3);
		Scale(o,0.8,0.8,0.8);
		Translate(o,2.5,-1.0,6.0);
		invert(&o->T[0][0],&o->Tinv[0][0]);
		insertObject(o,object_list);

  	}
}

void rtShade(int internal, struct object3D *obj, struct point3D *p, struct point3D *n, struct ray3D *ray, int maxDepth, int depth, double a, double b, struct colourRGB *col, struct object3D *object_list, struct pointLS *light_list, struct textureNode *texture_list) {
	// This function implements the shading model as described in lecture. It takes
	// - A pointer to the first object intersected by the ray (to get the colour properties)
	// - The coordinates of the intersection point (in world coordinates)
	// - The normal at the point
	// - The ray (needed to determine the reflection direction to use for the global component, as well as for
	//   the Phong specular component)
	// - The current recursion depth
	// - The (a,b) texture coordinates (meaningless unless texture is enabled)
	//
	// Returns:
	// - The colour for this ray (using the col pointer)
	//
	double R,G,B;			// Colour for the object in R G and B
	// This will hold the colour as we process all the components of
	// the Phong illumination model

	if (obj->texImg == NULL) {
 		R = obj->col.R;
 		G = obj->col.G;
 		B = obj->col.B;
	} else {
  		// Get object colour from the texture given the texture coordinates (a,b), and the texturing function
  		// for the object. Note that we will use textures also for Photon Mapping.
 		obj->textureMap(obj->texImg, a, b, &R, &G, &B);
	}

 	//Used to traverse over the lights.
 	struct pointLS *curLight;
 	struct object3D *curAreaLight;

 	//Object/light intercept variables.
 	struct point3D interceptP;
 	struct point3D interceptN;
 	struct object3D *interceptObj;

 	//Local lighting variables.
 	struct colourRGB localLight;
 	struct ray3D *tRay;
 	struct point3D p0;
 	struct point3D d;
 	double distLambda;
 	int i, j;
 	struct point3D areaPoint;
 	struct point3D areaVector;
 	struct colourRGB areaLight;
 	int totalSamples;
 	double sampleDist;
 	double noiseX, noiseY;

 	//Phong variables.
 	double factor;
 	struct point3D m;
 	struct point3D de;

 	//Global lighting variables.
 	struct colourRGB globalLight;
 	struct ray3D *mRay;
 	struct point3D mp0;
 	struct point3D md;

 	//Ambient light component.
	localLight.R = (obj->alb.ra * R);
	localLight.G = (obj->alb.ra * G);
	localLight.B = (obj->alb.ra * B);

	if (obj->alb.rs > 0.0 || obj->alb.rd > 0.0) {

	 	//Area light sources. Processed the same way as point light sources
	 	//except using multiple rays and stochastic sampling of a plane
	 	curAreaLight = object_list;
	 	while (curAreaLight != NULL) {
	 		if (curAreaLight->isLightSource) {

	 			areaLight.R = 0.0;
				areaLight.G = 0.0;
				areaLight.B = 0.0;
	 			
	 			sampleDist = 1.0 / 4.0;
	 			totalSamples = 0;

	 			for (i = 0; i < 4.0; i++) {
	 				for (j = 0; j < 4.0; j++) {

	 					//Find our sample point
	 					noiseX = drand48() * sampleDist;
	 					noiseY = drand48() * sampleDist;
	 					planeCoordinates(curAreaLight, ((i * sampleDist) + noiseX), ((j * sampleDist) + noiseY), &areaPoint.px, &areaPoint.py, &areaPoint.pz);
	 					areaPoint.pw = 1.0;

	 					//Shoot our ray
	 					memcpy(&p0, p, sizeof(struct point3D));
	 					memcpy(&d, &areaPoint, sizeof(struct point3D));
		 				subVectors(&p0,&d);
		 				tRay = newRay(&p0, &d);
		 				findFirstHit(tRay, &distLambda, obj, &interceptObj, &interceptP, &interceptN, &a, &b, object_list);
		 				free(tRay);

		 				//If we aren't in shadow
		 				if (!((0.0 < distLambda) && (distLambda < 0.99999999))) {

		 					//Compute and weigh diffusion
					 		normalize(&d);
					 		factor = dot(n, &d);
					 		if (factor > 0.0) {
					 			factor *= obj->alb.rd;
						 		areaLight.R += (factor * curAreaLight->col.R);
								areaLight.G += (factor * curAreaLight->col.G);
								areaLight.B += (factor * curAreaLight->col.B);
								factor /= obj->alb.rd;
							}

							//Compute and weigh specular component
							memcpy(&m, n, sizeof(struct point3D));
							scalarVecMult((2 * factor), &m);
							subVectors(&d, &m);
							memcpy(&de, &ray->d, sizeof(struct point3D));
							normalize(&de);
							scalarVecMult(-1, &de);
							factor = dot(&m ,&de);
							if (factor > 0.0) {
						 		factor = pow(factor, obj->shinyness);
						 		factor *= obj->alb.rs;
						 		areaLight.R += (factor * curAreaLight->col.R);
						 		areaLight.G += (factor * curAreaLight->col.G);
						 		areaLight.B += (factor * curAreaLight->col.B);
					 		}
		 				}

		 				totalSamples++;

	 				}
	 			}

	 			//Add our area light source's light to the local light by averaging the sample results
	 			areaLight.R /= totalSamples;
				areaLight.G /= totalSamples;
				areaLight.B /= totalSamples;
	 			localLight.R += areaLight.R;
				localLight.G += areaLight.G;
				localLight.B += areaLight.B;

	 		}

	 		curAreaLight = curAreaLight->next;

	 	}

	 	//Point light sources.
	 	curLight = light_list;
	 	while (curLight != NULL) {

		 	//Determine ray from the intersection point to the light
		 	memcpy(&p0, p, sizeof(struct point3D));
		 	memcpy(&d, &curLight->p0, sizeof(struct point3D));
		 	subVectors(&p0,&d);

		 	//Determine if we intersect any objects on the way to the light
		 	tRay = newRay(&p0, &d);
		 	findFirstHit(tRay, &distLambda, obj, &interceptObj, &interceptP, &interceptN, &a, &b, object_list);
		 	free(tRay);

		 	//If we aren't in a shadow, compute the Phong model
		 	if (!((0.0 < distLambda) && (distLambda < 0.99999999))) {

		 		// Diffuse component
		 		normalize(&d);
		 		factor = dot(n, &d);
		 		if (factor > 0.0) {
		 			factor *= obj->alb.rd;
			 		localLight.R += (factor * curLight->col.R);
					localLight.G += (factor * curLight->col.G);
					localLight.B += (factor * curLight->col.B);
					factor /= obj->alb.rd;
				}
				
				//Specular component
				memcpy(&m, n, sizeof(struct point3D));
				scalarVecMult((2 * factor), &m);
				subVectors(&d, &m);
				memcpy(&de, &ray->d, sizeof(struct point3D));
				normalize(&de);
				scalarVecMult(-1, &de);
				factor = dot(&m ,&de);
				if (factor > 0.0) {
			 		factor = pow(factor, obj->shinyness);
			 		factor *= obj->alb.rs;
			 		localLight.R += (factor * curLight->col.R);
			 		localLight.G += (factor * curLight->col.G);
			 		localLight.B += (factor * curLight->col.B);
		 		}
		 	} //End of Phong model

		 	//Iterate to the next light
		 	curLight = curLight->next;
		}
	}

	//Global light component
	globalLight.R = 0.0;
	globalLight.G = 0.0;
	globalLight.B = 0.0;
	if (depth < maxDepth) {
	 	if (obj->alb.rg > 0.0) {

			//Compute the mirror ray
			memcpy(&mp0, p, sizeof(struct point3D));
			memcpy(&md, n, sizeof(struct point3D));
			scalarVecMult((2 * dot(n, &de)), &md);
			subVectors(&de, &md);

			//Shoot the ray!
			mRay = newRay(&mp0, &md);
			rayTrace(mRay, maxDepth, depth+1, &globalLight, obj, object_list, light_list, texture_list);
			free(mRay);
			
			//Scale the colour
			globalLight.R *= obj->alb.rg;
			globalLight.G *= obj->alb.rg;
			globalLight.B *= obj->alb.rg;
		}

		//Refraction
		if (obj->alpha < 1.0) {

			struct colourRGB refrCol;
			refrCol.R = 0.0;
			refrCol.G = 0.0;
			refrCol.B = 0.0;

			//If the r_index is 1, there won't be refraction so just shoot another ray in the same direction
			if (obj->r_index == 1.0) {

				mRay = newRay(p, &ray->d);
				rayTrace(mRay, maxDepth, depth+1, &refrCol, obj, object_list, light_list, texture_list);
				free(mRay);

			} else {

				double beta = obj->r_index;
				double factor2;
				memcpy(&mp0, &ray->d, sizeof(struct point3D));
				memcpy(&md, n, sizeof(struct point3D));

				//If we're inside a refractive object, we modify the r_index
				if (internal) { beta = 1.0 / beta; }

				//Compute the portions of the refraction ray
				factor = dot(n, &mp0);
				factor2 = 1 - ((beta * beta) * (1 - (factor * factor)));

				//If it isn't total internal refraction, continue our computation
				if (factor2 > 0.0) {

					//Finish calculating the ray and shoot it
					factor = (beta * factor) - sqrt(factor2);
					scalarVecMult(beta, &mp0);
					scalarVecMult(factor, &md);
					addVectors(&mp0, &md);
					mRay = newRay(p, &md);
					findFirstHit(mRay, &distLambda, NULL, &interceptObj, &interceptP, &interceptN, &a, &b, object_list);

					if (distLambda > 0.0) {

						//If the current ray isn't inside an object
						if (!internal) {

							//If the intersection object has volume, the ray shot will be internal, so the normal is swapped
							if (obj->hasVolume && interceptObj == obj) {

								scalarVecMult(-1, &interceptN);
								rtShade(1, interceptObj, &interceptP, &interceptN, mRay, maxDepth, depth+1, a, b, &refrCol, object_list, light_list, texture_list);
				
							} else {

								//Intersecting with an object inside the refractive object? Not completely implemented
								rayTrace(mRay, maxDepth, depth+1, &refrCol, obj, object_list, light_list, texture_list);

							}

						} else {

							//The ray is internal so it shouldn't collide with itself, retrace ray
							if (interceptObj == obj) {

								rayTrace(mRay, maxDepth, depth+1, &refrCol, obj, object_list, light_list, texture_list);

							} else {

								//Otherwise shade as usual
								rtShade(0, interceptObj, &interceptP, &interceptN, mRay, maxDepth, depth+1, a, b, &refrCol, object_list, light_list, texture_list);

							}
						}
					}
					
					free(mRay);
				}
			}

			//Add the refractive component to the global light
			globalLight.R += refrCol.R * (1.0 - obj->alpha);
			globalLight.G += refrCol.G * (1.0 - obj->alpha);
			globalLight.B += refrCol.B * (1.0 - obj->alpha);

		}
	}
 
	col->R = globalLight.R + localLight.R;
	col->G = globalLight.G + localLight.G;
	col->B = globalLight.B + localLight.B;

	//Check that we don't over or underflow our colour components
	if (col->R > 1.0) { col->R = 1.0; }
	if (col->G > 1.0) { col->G = 1.0; }
	if (col->B > 1.0) { col->B = 1.0; }
	if (col->R < 0.0) { col->R = 0.0; }
	if (col->G < 0.0) { col->G = 0.0; }
	if (col->B < 0.0) { col->B = 0.0; }

	//Free some junk.
	free(curLight);
}

void findFirstHit(struct ray3D *ray, double *lambda, struct object3D *Os, struct object3D **obj, struct point3D *p, struct point3D *n, double *a, double *b, struct object3D *object_list) {
	// Find the closest intersection between the ray and any objects in the scene.
	// Inputs:
	//   *ray    -  A pointer to the ray being traced
	//   *Os     -  'Object source' is a pointer toward the object from which the ray originates. It is used for reflected or refracted rays
	//              so that you can check for and ignore self-intersections as needed. It is NULL for rays originating at the center of
	//              projection
	// Outputs:
	//   *lambda -  A pointer toward a double variable 'lambda' used to return the lambda at the intersection point
	//   **obj   -  A pointer toward an (object3D *) variable so you can return a pointer to the object that has the closest intersection with
	//              this ray (this is required so you can do the shading)
	//   *p      -  A pointer to a 3D point structure so you can store the coordinates of the intersection point
	//   *n      -  A pointer to a 3D point structure so you can return the normal at the intersection point
	//   *a, *b  -  Pointers toward double variables so you can return the texture coordinates a,b at the intersection point

	double cLambda;
	struct object3D *curObj;
	struct point3D cPoint;
	struct point3D cNormal;
	double cA, cB;

	cPoint.px = 0.0;
	cPoint.py = 0.0;
	cPoint.pz = 0.0;
	cPoint.pw = 1.0;

	cNormal.px = 0.0;
	cNormal.py = 0.0;
	cNormal.pz = 0.0;
	cNormal.pw = 1.0;
	
	*lambda = -1.0;

	curObj = object_list;
	while (curObj != NULL) {

		//Make sure we don't try to intersect with ourself.
		if (!(curObj == Os)) {
			
			//Get the intersection with the current object.
			curObj->intersect(curObj, ray, &cLambda, &cPoint, &cNormal, &cA, &cB);

			//We get a bit of noise here that we have to deal with.
			if ((*lambda < 0.00000001 || cLambda < *lambda) && (cLambda > 0.00000001)){

				if (curObj->isBounding) {

					//If we hit a bounding box, check intersections with the objects inside it
					curObj = curObj->b_next;
					continue;

				} else {

					//Store the 'best' intersection.
					*lambda = cLambda;
					*obj = curObj;
					*p = cPoint;
					*n = cNormal;
					*a = cA;
					*b = cB;
				}
			}
		}

		curObj = curObj->next;
	}

}

void rayTrace(struct ray3D *ray, int maxDepth, int depth, struct colourRGB *col, struct object3D *Os, struct object3D *object_list, struct pointLS *light_list, struct textureNode *texture_list) {
	// Trace one ray through the scene.
	//
	// Parameters:
	//   *ray   -  A pointer to the ray being traced
	//   depth  -  Current recursion depth for recursive raytracing
	//   *col   - Pointer to an RGB colour structure so you can return the object colour
	//            at the intersection point of this ray with the closest scene object.
	//   *Os    - 'Object source' is a pointer to the object from which the ray 
	//            originates so you can discard self-intersections due to numerical
	//            errors. NULL for rays originating from the center of projection. 

	double lambda;		// Lambda at intersection
	double a,b;		// Texture coordinates
	struct object3D *obj;	// Pointer to object at intersection
	struct point3D p;	// Intersection point
	struct point3D n;	// Normal at intersection

	if (depth>maxDepth) {
		col->R = 0.0;
		col->G = 0.0;
		col->B = 0.0;
		return;
	}

 	//Find the closest intersection.
 	findFirstHit(ray, &lambda, Os, &obj, &p, &n, &a, &b, object_list);
 	if (lambda > 0.0) {

	 	//Determine the colour of the object at the point of intersection and copy it.
	 	rtShade(0, obj, &p, &n, ray, maxDepth, depth, a, b, col, object_list, light_list, texture_list);
 	} else {
	 	col->R = 0.0;
	 	col->G = 0.0;
	 	col->B = 0.0;
 	}
}

void setPixel(struct image *im, int i, int j, colourRGB col) {
	unsigned char *cData = (unsigned char *) im->rgbdata;
	int offset = (j * im->sx * 3) + (i * 3);
	*(cData + offset + 0) = col.R * 255;
	*(cData + offset + 1) = col.G * 255;
	*(cData + offset + 2) = col.B * 255;
}

void *rtThread(void *rtd) {

	//Threaded raytrace

	struct rtThreadData *args = (struct rtThreadData *) rtd;

	struct point3D p0, d, pHolder;
	struct ray3D *ray;
	struct colourRGB col;

	col.R = 0.0;
	col.G = 0.0;
	col.B = 0.0;

	int i, j;

	//Compute the section of the image we will render
	int left = (args->tID * (args->render_image->sx / args->numThreads));
	int right = ((args->tID + 1) * (args->render_image->sx / args->numThreads));

	if (args->vfx == 0) { //No antialiasing or depth of field
		for (j = 0; j < args->render_image->sy; j++) {
 			for (i = left; i < right; i++) {

				pHolder.px = args->view_cam->wl + (args->view_cam->du * i);
	 			pHolder.py = args->view_cam->wt + (args->view_cam->dv * j);
	 			pHolder.pz = args->view_cam->f;
	 			pHolder.pw = 1;

		  		//Convert to world coordinates
	 			matVecMult(args->view_cam->C2W, &pHolder);

				//Compute the origin of the ray.
	 			p0.px = pHolder.px;
	 			p0.py = pHolder.py;
	 			p0.pz = pHolder.pz;
	 			p0.pw = 1;
				//printf("p0:[%f, %f, %f, %f]\n", p0.px,p0.py,p0.pz,p0.pw);

				//Compute the direction of the ray.
	 			d.px = p0.px - args->view_cam->e.px;
	 			d.py = p0.py - args->view_cam->e.py;
	 			d.pz = p0.pz - args->view_cam->e.pz;
	 			d.pw = 1;
	 			normalize(&d);
				//printf("d:[%f, %f, %f, %f]\n", d.px,d.py,d.pz,d.pw);

	 			ray = newRay(&p0, &d);
	 			rayTrace(ray, args->maxDepth, 0, &col, NULL, args->object_list, args->light_list, args->texture_list);
	 			free(ray);

	 			//printf("%d SETTING PIXEL\n", args->tID);
	 			setPixel(args->render_image, i, j, col);
 			}
 		}
	} else if (args->vfx == 1) { //Antialiasing
		struct colourRGB aaCol;
		double sj, si;
		int aaSamples;

		for (j = 0; j < args->render_image->sy; j++) {
 			for (i = left; i < right; i++) {

				aaCol.R = 0.0;
				aaCol.G = 0.0;
				aaCol.B = 0.0;
				aaSamples = 0;

				//If antialiasing is enabled we supersample to determine the pixel colour
	 			for (sj = (j - 0.5); sj <= (j + 0.5); sj += 0.1) {
	 				for (si = (i - 0.5); si <= (i + 0.5); si += 0.1) {

	 					//Same method as without antialiasing
		 				pHolder.px = args->view_cam->wl + (args->view_cam->du * si);
		 				pHolder.py = args->view_cam->wt + (args->view_cam->dv * sj);
		 				pHolder.pz = args->view_cam->f;
		 				pHolder.pw = 1;
		 				matVecMult(args->view_cam->C2W, &pHolder);
		 				p0.px = pHolder.px;
		 				p0.py = pHolder.py;
		 				p0.pz = pHolder.pz;
		 				p0.pw = 1;
		 				d.px = p0.px - args->view_cam->e.px;
		 				d.py = p0.py - args->view_cam->e.py;
		 				d.pz = p0.pz - args->view_cam->e.pz;
		 				d.pw = 1;
		 				normalize(&d);
		 				ray = newRay(&p0, &d);
		 				rayTrace(ray, args->maxDepth, 0, &col, NULL, args->object_list, args->light_list, args->texture_list);
		 				free(ray);
		 				aaCol.R += col.R;
		 				aaCol.G += col.G;
		 				aaCol.B += col.B;
		 				aaSamples++;

	 				}
	 			}

	 			//Average our samples and use that as the colour
	 			aaCol.R /= aaSamples;
				aaCol.G /= aaSamples;
				aaCol.B /= aaSamples;
				col.R = aaCol.R;
				col.G = aaCol.G;
				col.B = aaCol.B;

	 			setPixel(args->render_image, i, j, col);
 			}
 		}
	} else if (args->vfx == 2) { //Depth of field

		double aperatureRadius = args->view_cam->aperatureRadius;
		struct point3D focalPoint;
		struct point3D aperaturePoint;
		double theta, length;
		double thetaI, lengthI;
		int dofSamples;

		struct colourRGB dofCol;

		//Initialize the aperature point
		aperaturePoint.px = 0.0;
		aperaturePoint.py = 0.0;
		aperaturePoint.pz = args->view_cam->e.pz;
		aperaturePoint.pw = 1.0;

		for (j = 0; j < args->render_image->sy; j++) {
 			for (i = left; i < right; i++) {
				
				//Compute a ray the same as regular tracing
 				pHolder.px = args->view_cam->wl + (args->view_cam->du * i);
	 			pHolder.py = args->view_cam->wt + (args->view_cam->dv * j);
	 			pHolder.pz = args->view_cam->f;
	 			pHolder.pw = 1;
	 			matVecMult(args->view_cam->C2W, &pHolder);
	 			p0.px = pHolder.px;
	 			p0.py = pHolder.py;
	 			p0.pz = pHolder.pz;
	 			p0.pw = 1;
	 			d.px = p0.px - args->view_cam->e.px;
	 			d.py = p0.py - args->view_cam->e.py;
	 			d.pz = p0.pz - args->view_cam->e.pz;
	 			d.pw = 1;
	 			normalize(&d);
	 			ray = newRay(&p0, &d);

	 			//Use that ray to find the focal point on the focal plane
	 			rayPosition(ray, args->view_cam->focalPlane, &focalPoint);
	 			free(ray);

	 			dofCol.R = 0.0;
				dofCol.G = 0.0;
				dofCol.B = 0.0;
				dofSamples = 0;

				//Sample points from the aperature to the focal point
 				for (thetaI = 0.0; thetaI < 1.0; thetaI += 0.1) {
 					for (lengthI = 0.0; lengthI <= 1.0; lengthI += 0.1) {

 						theta = thetaI * PI;
 						length = lengthI * aperatureRadius;

 						aperaturePoint.px = length * cos(theta);
						aperaturePoint.py = length * sin(theta);

		 				d.px = focalPoint.px - aperaturePoint.px;
		 				d.py = focalPoint.py - aperaturePoint.py;
		 				d.pz = focalPoint.pz - aperaturePoint.pz;
		 				d.pw = 1;
		 				normalize(&d);

		 				ray = newRay(&aperaturePoint, &d);
		 				rayTrace(ray, args->maxDepth, 0, &col, NULL, args->object_list, args->light_list, args->texture_list);
		 				free(ray);
		 				dofCol.R += col.R;
		 				dofCol.G += col.G;
		 				dofCol.B += col.B;
		 				dofSamples++;

 					}
 				}

 				//Average the results and use that as our colour
	 			dofCol.R /= dofSamples;
				dofCol.G /= dofSamples;
				dofCol.B /= dofSamples;
				col.R = dofCol.R;
				col.G = dofCol.G;
				col.B = dofCol.B;

	 			setPixel(args->render_image, i, j, col);
 			}
 		}
	}

 	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	srand48(time(NULL));
	int sceneSelect;
	int sx;		// Size of the raytraced image
	int sy;
	char output_name[1024];	// Name of the output file for the raytraced .ppm image
	struct point3D e;		// Camera view parameters 'e', 'g', and 'up'
	struct point3D g;
	struct point3D up;

	struct colourRGB background;   // Background colour

	struct object3D *object_list;
	struct pointLS *light_list;
	struct textureNode *texture_list;

	struct image *render_image;
	struct view *view_cam;
	int vfx;

	double aperatureR;
	double focalP;

	int numThreads;
	int maxDepth;

	if (argc < 10) {
		fprintf(stderr,"RayTracer: Can not parse input parameters\n");
		fprintf(stderr,"USAGE: RayTracer sceneselect sizex sizey rec_depth numThreads aa/dof aperatureRadius focalPlaneDistance output_name\n");
		fprintf(stderr,"   scene select, 0 for final scene, 1 for simple scene, 2 for refraction test, 3 for depth of field test\n");
		fprintf(stderr,"   sizex = Image width\n");
		fprintf(stderr,"   sizey = Image height\n");
		fprintf(stderr,"   rec_depth = Recursion depth\n");
		fprintf(stderr,"   numThreads = must be greater than 0\n");
		fprintf(stderr,"   vfx = 0 for none, 1 for antialiasing, 2 for depth of field\n");
		fprintf(stderr,"   aperatureRadius must be a positive float\n");
		fprintf(stderr,"   focalPlaneDistance must be a float\n");
		fprintf(stderr,"   output_name = Name of the output file, e.g. MyRender.ppm\n");
		exit(0);
	}

	if (atoi(argv[1])==1) {
		fprintf(stderr,"Rendering simple scene\n");
 		sceneSelect = 1;
	} else if (atoi(argv[1])==2) {
		fprintf(stderr,"Rendering refraction test\n");
 		sceneSelect = 2;
	} else if (atoi(argv[1])==3) {
		fprintf(stderr,"Rendering depth of field test\n");
		sceneSelect = 3;
	} else {
		fprintf(stderr,"Rendering final scene\n");
		sceneSelect = 0;
	}

	sx=atoi(argv[2]);
	sy=atoi(argv[3]);

	maxDepth=atoi(argv[4]);

	numThreads=atoi(argv[5]);

	if (atoi(argv[6]) == 0) {
		fprintf(stderr,"Antialiasing and depth of field disabled\n");
 		vfx = 0;
	} else if (atoi(argv[6]) == 1) {
		fprintf(stderr,"Antialiasing enabled\n");
 		vfx = 1;
	} else if (atoi(argv[6]) == 2) {
		fprintf(stderr,"Depth of field enabled\n");
		vfx = 2;
	} else {
		fprintf(stderr,"Antialiasing and depth of field disabled\n");
 		vfx = 0;
	}

	aperatureR = abs(atof(argv[7]));
	if (aperatureR == 0.0) {
		aperatureR = 0.3;
	}
	fprintf(stderr,"Aperature radius set to %f\n", aperatureR);

	if (atof(argv[8]) == 0.0) {
		focalP = 3.0;
	} else {
		focalP = atof(argv[8]);
	}
	fprintf(stderr,"Focal plane distance set to %f\n", focalP);

	strcpy(&output_name[0],argv[9]);

	fprintf(stderr,"Rendering image at %d x %d\n",sx,sy);
	fprintf(stderr,"Recursion depth = %d\n",maxDepth);

	if (numThreads < 1) {
		fprintf(stderr,"Settings number of threads to one.\n");
	} else {
		fprintf(stderr,"%d thread(s).\n", numThreads);
	}

	fprintf(stderr,"Output file name: %s\n",output_name);

	object_list=NULL;
	light_list=NULL;
	texture_list=NULL;

	// Allocate memory for the new image
	render_image=newImage(sx, sy);
	if (!render_image) {
 		fprintf(stderr,"Unable to allocate memory for raytraced image\n");
 		exit(0);
	}

 	buildScene(sceneSelect, &object_list, &light_list, &texture_list);

	// Camera center is at (0,0,-1)
	e.px=0;
	e.py=0;
	e.pz=-2;
	e.pw=1;

	// To define the gaze vector, we choose a point 'pc' in the scene that
	// the camera is looking at, and do the vector subtraction pc-e.
	// Here we set up the camera to be looking at the origin.
	g.px=0-e.px;
	g.py=0-e.py;
	g.pz=0-e.pz;
	g.pw=1;
	// In this case, the camera is looking along the world Z axis, so
	// vector w should end up being [0, 0, -1]

	// Define the 'up' vector to be the Y axis
	up.px=0;
	up.py=1;
	up.pz=0;
	up.pw=1;

	double ratio = ((float) sx) / ((float) sy);
	double wadth = 4.0;
	double higth = wadth/ratio;

	view_cam=setupView(&e, &g, &up, -2, -(wadth/2), (higth/2), wadth, higth);

	if (view_cam==NULL) {
 		fprintf(stderr,"Unable to set up the view and camera parameters. Out of memory!\n");
 		cleanup(object_list,light_list, texture_list);
 		deleteImage(render_image);
 		exit(0);
	}

 	// Set up background colour here
 	background.R=0;
 	background.G=0;
 	background.B=0;

	// du and dv. In the notes in terms of wl and wr, wt and wb,
	// here we use wl, wt, and wsize. du=dv since the image is
	// and dv is negative since y increases downward in pixel
	// coordinates and upward in camera coordinates.
	view_cam->du=view_cam->wwidth/(sx-1);	
	view_cam->dv=-view_cam->wheight/(sy-1);

	//Depth of field paramters
  	view_cam->aperatureRadius = aperatureR;
 	view_cam->focalPlane = focalP;

	fprintf(stderr,"View parameters:\n");
	fprintf(stderr,"Left=%f, Top=%f, Width=%f, Height=%f, f=%f\n",view_cam->wl,view_cam->wt,view_cam->wwidth,view_cam->wheight,view_cam->f);
	fprintf(stderr,"\nCamera to world conversion matrix:\n");
	printmatrix(view_cam->C2W);
	fprintf(stderr,"\nWorld to camera conversion matrix:\n");
	printmatrix(view_cam->W2C);
	fprintf(stderr,"\n");

	printf("RENDERING\n");

	clock_t start = clock();

	// Something is preventing this from actually utilizing multiple processing threads.
	// Never got around to fixing it.

	pthread_t threads[numThreads];
    struct rtThreadData rtargs[numThreads];
    int t, i;

	for (i = 0; i < numThreads; i++) {
		rtargs[i].tID = i;
		rtargs[i].object_list = object_list;
		rtargs[i].light_list = light_list;
		rtargs[i].texture_list = texture_list;
		rtargs[i].render_image = render_image;
		rtargs[i].view_cam = view_cam;
		rtargs[i].vfx = vfx;
		rtargs[i].numThreads = numThreads;
		rtargs[i].maxDepth = maxDepth;

		t = pthread_create(&threads[i], NULL, rtThread, (void *)&rtargs[i]);

		if (t) {
			printf("Error creating threads\n");
			exit(0);
		}
	}

	for (i = 0; i < numThreads; i++) {
		t = pthread_join(threads[i], NULL);
		if (t) {
         	printf("Error joining threads\n");
         	exit(0);
      	}
	}

	fprintf(stderr,"RENDER COMPLETE\n");

	// Output rendered image
	imageOutput(render_image, output_name);

	clock_t end = clock();
	double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
	printf("TIME: %f\n", time);

	// Exit section. Clean up and return.
	cleanup(object_list,light_list,texture_list);		// Object, light, and texture lists
	deleteImage(render_image);					// Rendered image
	free(view_cam);						// camera view

	pthread_exit(NULL);
	//exit(0);
}
