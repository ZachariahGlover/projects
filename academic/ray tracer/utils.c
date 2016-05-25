/*
   utils.c - F.J. Estrada, Dec. 9, 2010
   Last updated: Aug. 12, 2014  -  F.J.E.

   Utilities for the ray tracer. You will need to complete
   some of the functions in this file. Look for the sections
   marked "TO DO". Be sure to read the rest of the file and
   understand how the entire code works.
*/

#include "utils.h"

// A useful 4x4 identity matrix which can be used at any point to
// initialize or reset object transformations
double eye4x4[4][4]={{1.0, 0.0, 0.0, 0.0},
                    {0.0, 1.0, 0.0, 0.0},
                    {0.0, 0.0, 1.0, 0.0},
                    {0.0, 0.0, 0.0, 1.0}};

/////////////////////////////////////////////
// Primitive data structure section
/////////////////////////////////////////////
struct point3D *newPoint(double px, double py, double pz) {
  // Allocate a new point structure, initialize it to
  // the specified coordinates, and return a pointer
  // to it.

  struct point3D *pt=(struct point3D *)calloc(1,sizeof(struct point3D));
  if (!pt) {
    fprintf(stderr,"Out of memory allocating point structure!\n");
  } else {
    pt->px=px;
    pt->py=py;
    pt->pz=pz;
    pt->pw=1.0;
  }
  return(pt);
}

struct pointLS *newPLS(struct point3D *p0, double r, double g, double b) {
  // Allocate a new point light sourse structure. Initialize the light
  // source to the specified RGB colour
  // Note that this is a point light source in that it is a single point
  // in space, if you also want a uniform direction for light over the
  // scene (a so-called directional light) you need to place the
  // light source really far away.

  struct pointLS *ls=(struct pointLS *)calloc(1,sizeof(struct pointLS));
  if (!ls) {
    fprintf(stderr,"Out of memory allocating light source!\n");
  } else {
    memcpy(&ls->p0,p0,sizeof(struct point3D));	// Copy light source location
    ls->col.R=r;					// Store light source colour and
    ls->col.G=g;					// intensity
    ls->col.B=b;
  }
  return(ls);
}

/////////////////////////////////////////////
// Ray and normal transforms
/////////////////////////////////////////////
inline void rayTransform(struct ray3D *ray_orig, struct ray3D *ray_transformed, struct object3D *obj) {
  // Transforms a ray using the inverse transform for the specified object. This is so that we can
  // use the intersection test for the canonical object. Note that this has to be done carefully!
 
  //Generate two points to transform.
  struct point3D *point = newPoint(ray_orig->p0.px, ray_orig->p0.py, ray_orig->p0.pz);
  struct point3D *direction = newPoint(ray_orig->d.px, ray_orig->d.py, ray_orig->d.pz);
  addVectors(point, direction);

  //Transform those two points.
  matVecMult(obj->Tinv, point);
  matVecMult(obj->Tinv, direction);
 
  //Get the new direction vector.
  subVectors(point, direction);

  //Copy the components to the transformed ray.
  memcpy(&ray_transformed->p0,point,sizeof(struct point3D));
  memcpy(&ray_transformed->d,direction,sizeof(struct point3D));
 
  free(point);
  free(direction);
}

inline void normalTransform(struct point3D *n_orig, struct point3D *n_transformed, struct object3D *obj) {
  // Computes the normal at an affinely transformed point given the original normal and the
  // object's inverse transformation. From the notes:
  // n_transformed=A^-T*n normalized.

  struct point3D *norm = newPoint(n_orig->px, n_orig->py, n_orig->pz);
 
  //Get the transpose of our inverse transformation matrix.
  double TinvT[4][4];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      TinvT[i][j] = obj->Tinv[j][i];
    }
  }

  //We don't want the translation component.
  TinvT[0][3] = 0.0;
  TinvT[1][3] = 0.0;
  TinvT[2][3] = 0.0;
  TinvT[3][0] = 0.0;
  TinvT[3][1] = 0.0;
  TinvT[3][2] = 0.0;
  TinvT[3][3] = 1.0;
 
  //Compute the vector and normalize it.
  matVecMult(TinvT, norm);
  normalize(norm);

  //Copy and free the vector.
  memcpy(n_transformed,norm,sizeof(struct point3D));
  free(norm);
}

/////////////////////////////////////////////
// Object management section
/////////////////////////////////////////////
void insertObject(struct object3D *o, struct object3D **list) {
  if (o==NULL) return;
  // Inserts an object into the object list.
  if (*(list)==NULL) {
    *(list)=o;
    (*(list))->next=NULL;
  } else {
    o->next=(*(list))->next;
    (*(list))->next=o;
  }
}

void insertBoundedObject(struct object3D *b, struct object3D *o, struct object3D **list) {
  if (o == NULL) return;
  // Inserts an object into the object list.
  if (*(list) == NULL) {
    *(list) = o;
    (*(list))->next = b->next;
  } else {
    o->next = (*(list))->next;
    (*(list))->next = o;
  }
}

struct object3D *newPlane(double ra, double rd, double rs, double rg, double r, double g, double b, double alpha, double r_index, double shiny) {
  // Intialize a new plane with the specified parameters:
  // ra, rd, rs, rg - Albedos for the components of the Phong model
  // r, g, b, - Colour for this plane
  // alpha - Transparency, must be set to 1 unless you are doing refraction
  // r_index - Refraction index if you are doing refraction.
  // shiny - Exponent for the specular component of the Phong model
  //
  // The plane is defined by the following vertices (CCW)
  // (1,1,0), (-1,1,0), (-1,-1,0), (1,-1,0)
  // With normal vector (0,0,1) (i.e. parallel to the XY plane)

  struct object3D *plane=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!plane) {
    fprintf(stderr,"Unable to allocate new plane, out of memory!\n");
  } else {
    plane->hasVolume=0;
    plane->alb.ra=ra;
    plane->alb.rd=rd;
    plane->alb.rs=rs;
    plane->alb.rg=rg;
    plane->col.R=r;
    plane->col.G=g;
    plane->col.B=b;
    plane->alpha=alpha;
    plane->r_index=r_index;
    plane->shinyness=shiny;
    plane->intersect=&planeIntersect;
    plane->surfaceCoords=&planeCoordinates;
    plane->randomPoint=&planeSample;
    plane->texImg=NULL;
    plane->photonMap=NULL;
    plane->normalMap=NULL;
    memcpy(&plane->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&plane->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    plane->textureMap=&texMap;
    plane->frontAndBack=1;
    plane->photonMapped=0;
    plane->normalMapped=0;
    plane->isCSG=0;
    plane->isLightSource=0;
    plane->CSGnext=NULL;
    plane->next=NULL;
  }
  return(plane);
}

struct object3D *newSphere(double ra, double rd, double rs, double rg, double r, double g, double b, double alpha, double r_index, double shiny) {
  // Intialize a new sphere with the specified parameters:
  // ra, rd, rs, rg - Albedos for the components of the Phong model
  // r, g, b, - Colour for this plane
  // alpha - Transparency, must be set to 1 unless you are doing refraction
  // r_index - Refraction index if you are doing refraction.
  // shiny -Exponent for the specular component of the Phong model
  //
  // This is assumed to represent a unit sphere centered at the origin.
  //

  struct object3D *sphere=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!sphere) {
    fprintf(stderr,"Unable to allocate new sphere, out of memory!\n");
  } else {
    sphere->hasVolume=1;
    sphere->alb.ra=ra;
    sphere->alb.rd=rd;
    sphere->alb.rs=rs;
    sphere->alb.rg=rg;
    sphere->col.R=r;
    sphere->col.G=g;
    sphere->col.B=b;
    sphere->alpha=alpha;
    sphere->r_index=r_index;
    sphere->shinyness=shiny;
    sphere->intersect=&sphereIntersect;
    sphere->surfaceCoords=&sphereCoordinates;
    sphere->randomPoint=&sphereSample;
    sphere->texImg=NULL;
    sphere->photonMap=NULL;
    sphere->normalMap=NULL;
    memcpy(&sphere->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&sphere->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    sphere->textureMap=&texMap;
    sphere->frontAndBack=0;
    sphere->photonMapped=0;
    sphere->normalMapped=0;
    sphere->isCSG=0;
    sphere->isLightSource=0;
    sphere->CSGnext=NULL;
    sphere->next=NULL;
  }
  return(sphere);
}

struct object3D *newCyl(double ra, double rd, double rs, double rg, double r, double g, double b, double alpha, double R_index, double shiny) {
  struct object3D *cylinder=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!cylinder) {
    fprintf(stderr,"Unable to allocate new cylinder, out of memory!\n");
  } else {
    cylinder->hasVolume=1;
    cylinder->alb.ra=ra;
    cylinder->alb.rd=rd;
    cylinder->alb.rs=rs;
    cylinder->alb.rg=rg;
    cylinder->col.R=r;
    cylinder->col.G=g;
    cylinder->col.B=b;
    cylinder->alpha=alpha;
    cylinder->r_index=R_index;
    cylinder->shinyness=shiny;
    cylinder->intersect=&cylIntersect;
    cylinder->surfaceCoords=&cylCoordinates;
    cylinder->randomPoint=&cylSample;
    cylinder->texImg=NULL;
    cylinder->photonMap=NULL;
    cylinder->normalMap=NULL;
    memcpy(&cylinder->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&cylinder->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    cylinder->textureMap=&texMap;
    cylinder->frontAndBack=0;
    cylinder->photonMapped=0;
    cylinder->normalMapped=0;
    cylinder->isCSG=0;
    cylinder->isLightSource=0;
    cylinder->CSGnext=NULL;
    cylinder->next=NULL;
  }
  return(cylinder);
}

struct object3D *newBox(double ra, double rd, double rs, double rg, double r, double g, double b, double alpha, double r_index, double shiny) {
  struct object3D *box=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!box) {
    fprintf(stderr,"Unable to allocate new box, out of memory!\n");
  } else {
    box->hasVolume=1;
    box->alb.ra=ra;
    box->alb.rd=rd;
    box->alb.rs=rs;
    box->alb.rg=rg;
    box->col.R=r;
    box->col.G=g;
    box->col.B=b;
    box->alpha=alpha;
    box->r_index=r_index;
    box->shinyness=shiny;
    box->intersect=&boxIntersect;
    box->surfaceCoords=&boxCoordinates;
    box->randomPoint=&boxSample;
    box->texImg=NULL;
    box->photonMap=NULL;
    box->normalMap=NULL;
    memcpy(&box->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&box->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    box->textureMap=&texMap;
    box->frontAndBack=0;
    box->photonMapped=0;
    box->normalMapped=0;
    box->isCSG=0;
    box->isLightSource=0;
    box->CSGnext=NULL;
    box->next=NULL;
  }
  return(box);
}

void planeIntersect(struct object3D *plane, struct ray3D *ray, double *lambda, struct point3D *p, struct point3D *n, double *a, double *b) {
  // Computes and returns the value of 'lambda' at the intersection
  // between the specified ray and the specified canonical plane.
  
  //Transform the ray we'll be checking for intersections with.
  struct ray3D *tRay = newRay(&ray->p0, &ray->d);
  rayTransform(ray, tRay, plane);
 
  //Get a point and the normal from the canonical plane.
  struct point3D *canPoint = newPoint(0.0, 0.0, 0.0);
  struct point3D *canNorm = newPoint(0.0, 0.0, 1.0);

  //Determine if there will be an intersection.
  subVectors(&tRay->p0, canPoint);
  double num = dot(canPoint, canNorm);
  double de = dot(&tRay->d, canNorm);

  if (de != 0.0) {

    //Compute our lambda for the intersection.
    *lambda = num/de;

    //Get the transformed ray position at the intersection.
    rayPosition(tRay, *lambda, p);

    //Bound the plane of intersection.
    if ((p->px <= 1 && p->px >= -1) && (p->py <= 1 && p->py >= -1)) {

      //Find the actual ray's position and compute the normal.
      rayPosition(ray, *lambda, p);
      normalTransform(canNorm, n, plane);

      //Get texture coordinates.
      struct point3D planePoint;
      memcpy(&planePoint, p, sizeof(struct point3D));
      matVecMult(plane->Tinv, &planePoint);
      *a = (planePoint.px + 1.0) / 2.0;
      *b = (planePoint.py + 1.0) / 2.0;
    } else {

      //Intersects outside the square.
      *lambda = -1.0;
    }
  } else {

    //Ray doesn't intersect.
    *lambda = -1.0;
  }

  free(tRay);
  free(canPoint);
  free(canNorm);
}

void sphereIntersect(struct object3D *sphere, struct ray3D *ray, double *lambda, struct point3D *p, struct point3D *n, double *a, double *b) {
  // Computes and returns the value of 'lambda' at the intersection
  // between the specified ray and the specified canonical sphere.

  //Uses the method described in the lecture notes to determine the ray sphere intersection.
  struct ray3D *tRay = newRay(&ray->p0, &ray->d);
  rayTransform(ray, tRay, sphere);

  double A,B,C,D;
  A = dot(&tRay->d, &tRay->d);
  B = dot(&tRay->p0, &tRay->d);
  C = dot(&tRay->p0, &tRay->p0) - 1;
  D = (B * B) - (A * C);

  if (D >= 0.0) {
    //Compute our two potential intersections.
    double l1, l2;
    l1 = -(B / A) + (sqrt(D) / A);
    l2 = -(B / A) - (sqrt(D) / A);

    //Decide which lambda to return (if any).
    //Returns the closest lambda in front of the camera.
    if (l1 < 0.0 && l2 < 0.0) {
      *lambda = -1.0;
    } else {
      if (l1 > 0.0 && l2 < 0.0000001) {
        *lambda = l1;
      } else if (l2 > 0.0 && l1 < 0.0000001){
        *lambda = l2;
      } else if (l1 < l2) {
        *lambda = l1;
      } else {
        *lambda = l2;
      }

      //Determine the normal, texture coordinates and intersection point.
      rayPosition(tRay, *lambda, p);
      normalTransform(p, n, sphere);
      *a = 0.5 + (atan2(p->pz, p->px) / (2 * PI));
      *b = 0.5 - (asin(p->py) / PI);
      rayPosition(ray, *lambda, p);
    }
  } else {
    *lambda = -1.0;
  }
  free(tRay);
}

void cylIntersect(struct object3D *cylinder, struct ray3D *ray, double *lambda, struct point3D *p, struct point3D *n, double *a, double *b) {
  // Computes and returns the value of 'lambda' at the intersection
  // between the specified ray and the specified canonical cylinder.
 
  struct ray3D *tRay = newRay(&ray->p0, &ray->d);
  rayTransform(ray, tRay, cylinder);

  //Variables for checking for intersects with the caps.
  struct point3D capIntersect;
  struct point3D capPoint;
  struct point3D capNorm;
  double nume, denom;
  double capLambda;
  double capRadius;
  double tempLambda;

  struct point3D *helpfulPoint = newPoint(0.0, 0.0, 1.0);
 
  //Check for intersection with the top.
  memcpy(&capPoint, helpfulPoint, sizeof(struct point3D));
  memcpy(&capNorm, helpfulPoint, sizeof(struct point3D));
  normalize(&capNorm);
  subVectors(&tRay->p0, &capPoint);
  nume = dot(&capPoint, &capNorm);
  denom = dot(&tRay->d, &capNorm);
  if (denom != 0.0) {
    capLambda = nume/denom;
    rayPosition(tRay, capLambda, &capPoint);
    capRadius = sqrt((capPoint.px * capPoint.px) + (capPoint.py * capPoint.py));
    if (capRadius > 1.0) {
      capLambda = -1.0;
    }
  } else {
    capLambda = -1.0;
  }
 
  //Check for intersection with the bottom and compare it to the top.
  scalarVecMult(-1.0, helpfulPoint);
  memcpy(&capPoint, helpfulPoint, sizeof(struct point3D));
  subVectors(&tRay->p0, &capPoint);
  nume = dot(&capPoint, &capNorm);
  denom = dot(&tRay->d, &capNorm);
  if (denom != 0.0) {
    tempLambda = nume/denom;
    if (tempLambda > 0.0) {
      if (tempLambda < capLambda || capLambda < 0.0) {
        rayPosition(tRay, tempLambda, &capPoint);
        capRadius = sqrt((capPoint.px * capPoint.px) + (capPoint.py * capPoint.py));
        if (capRadius > 1.0) {
          scalarVecMult(-1.0, &capNorm);
        } else {
          capLambda = tempLambda;
        }
      }
    } else {
      scalarVecMult(-1.0, &capNorm);
    }
 }
 rayPosition(tRay, capLambda, helpfulPoint);
 *a = (helpfulPoint->px + 1.0) / 2.0;
 *b = (helpfulPoint->py + 1.0) / 2.0;
 
  //Variables for checking intersections with the wall.
  double wallLambda;
  struct point3D wallNorm;
  double p0x = tRay->p0.px;
  double p0y = tRay->p0.py;
  double p0z = tRay->p0.pz;
  double dx = tRay->d.px;
  double dy = tRay->d.py;
  double dz = tRay->d.pz;
  double A,B,C,D;

  //Check the intersection with the wall.
  A = (dx * dx) + (dy * dy);
  B = (p0x * dx) + (p0y * dy);
  C = ((p0x * p0x) + (p0y * p0y)) - 1;
  D = (B * B) - (A * C);
  if (D >= 0.0) {
    double lw1, lw2;
    lw1 = -(B / A) + (sqrt(D) / A);
    lw2 = -(B / A) - (sqrt(D) / A);
    if (lw1 < 0.0 && lw2 < 0.0) {
      wallLambda = -1.0;
    } else {
      if (lw1 > 0.0 && lw2 < 0.0000001) {
        wallLambda = lw1;
      } else if (lw2 > 0.0 && lw1 < 0.0000001) {
        wallLambda = lw2;
      } else if (lw1 < lw2) {
        wallLambda = lw1;
      } else {
        wallLambda = lw2;
      }
      rayPosition(tRay, wallLambda, p);
      if (p->pz < 1 && p->pz > -1){
        normalTransform(p, &wallNorm, cylinder);
        rayPosition(ray, wallLambda, p);
      } else {
        wallLambda = -1.0;
      }
    }
  } else {
    wallLambda = -1.0;
  }
  rayPosition(tRay, wallLambda, helpfulPoint);

  //Compare the best intersections of the wall/caps.
  //Set the normal and modify texture coordinates accordingly.
  if (wallLambda > 0.0) {
    if (capLambda > 0.0) {
      if (capLambda < wallLambda) {
        *lambda = capLambda;
        normalTransform(&capNorm, n, cylinder);
      } else {
        *lambda = wallLambda;
        memcpy(n, &wallNorm, sizeof(struct point3D));
        *a = 0.5 + (atan2(helpfulPoint->py, helpfulPoint->px) / (2 * PI));
        *b = (helpfulPoint->pz + 1.0) / 2.0;
      }
    } else {
      *lambda = wallLambda;
      memcpy(n, &wallNorm, sizeof(struct point3D));
      *a = 0.5 + (atan2(helpfulPoint->py, helpfulPoint->px) / (2 * PI));
      *b = (helpfulPoint->pz + 1.0) / 2.0;
    }
  } else if (capLambda > 0.0) {
    *lambda = capLambda;
    normalTransform(&capNorm, n, cylinder);
  } else {
    *lambda = -1.0;
  }
  rayPosition(ray, *lambda, p);
  free(helpfulPoint);
  free(tRay);
}

void boxIntersect(struct object3D *box, struct ray3D *ray, double *lambda, struct point3D *p, struct point3D *n, double *a, double *b) {

  struct ray3D *tRay;
  struct point3D canPoints[6];
  struct point3D curPoint;
  struct point3D bestNorm;
  double cLambda = -1.0;
  double bLambda = -1.0;
  int bIndex = 0;

  for (int j = 0; j < 6; j++) {
    canPoints[j].px = 0.0;
    canPoints[j].py = 0.0;
    canPoints[j].pz = 0.0;
    canPoints[j].pw = 1.0;
  }

  canPoints[0].px = 1.0;
  canPoints[3].px = -1.0;
  canPoints[1].py = 1.0;
  canPoints[4].py = -1.0;
  canPoints[2].pz = 1.0;
  canPoints[5].pz = -1.0;

  tRay = newRay(&ray->p0, &ray->d);
  rayTransform(ray, tRay, box);
 
  for (int i = 0; i < 6; i++) {
    memcpy(&curPoint, &canPoints[i], sizeof(struct point3D));

    subVectors(&tRay->p0, &curPoint);
    double num = dot(&curPoint, &canPoints[i]);
    double de = dot(&tRay->d, &canPoints[i]);

    if (de != 0.0) {
      cLambda = num/de;
      rayPosition(tRay, cLambda, p);
      if ((p->px <= 1.00000001 && p->px >= -1.00000001) && (p->py <= 1.00000001 && p->py >= -1.00000001) && (p->pz <= 1.00000001 && p->pz >= -1.00000001)) {
        if ((cLambda > 0.0) && ((cLambda < bLambda) || (bLambda < 0.0))) {
          bIndex = i;
          bLambda = cLambda;
          memcpy(&bestNorm, &canPoints[i], sizeof(struct point3D));
        }
      }
    }
  }

  if (bLambda > 0.0) {
    rayPosition(ray, bLambda, p);
    normalTransform(&bestNorm, n, box);
    *lambda = bLambda;

    struct point3D planePoint;
    memcpy(&planePoint, p, sizeof(struct point3D));
    matVecMult(box->Tinv, &planePoint);
    if (bIndex % 3 == 0) {
      *a = (planePoint.pz + 1.0) / 2.0;
      *b = (planePoint.py + 1.0) / 2.0;
    } else if (bIndex % 3 == 1) {
      *a = (planePoint.px + 1.0) / 2.0;
      *b = (planePoint.pz + 1.0) / 2.0;
    } else {
      *a = (planePoint.px + 1.0) / 2.0;
      *b = (planePoint.py + 1.0) / 2.0;
    }

  } else {
    *lambda = -1.0;
  }

  free(tRay);
}

/////////////////////////////////////////////////////////////////
// Surface coordinates & random sampling on object surfaces
/////////////////////////////////////////////////////////////////
void planeCoordinates(struct object3D *plane, double a, double b, double *x, double *y, double *z) {
  // Return in (x,y,z) the coordinates of a point on the plane given by the 2 parameters a,b in [0,1].
  // 'a' controls displacement from the left side of the plane, 'b' controls displacement from the
  // bottom of the plane.
  struct point3D p;
  p.px = -1.0 + (2.0 * a);
  p.py = -1.0 + (2.0 * b);
  p.pz = 0.0;
  p.pw = 1.0;
  matVecMult(plane->T, &p);
  *x = p.px;
  *y = p.py;
  *z = p.pz;
}

void sphereCoordinates(struct object3D *sphere, double a, double b, double *x, double *y, double *z) {
  // Return in (x,y,z) the coordinates of a point on the plane given by the 2 parameters a,b.
  // 'a' in [0, 2*PI] corresponds to the spherical coordinate theta
  // 'b' in [-PI/2, PI/2] corresponds to the spherical coordinate phi
}

void cylCoordinates(struct object3D *cyl, double a, double b, double *x, double *y, double *z) {
  // Return in (x,y,z) the coordinates of a point on the plane given by the 2 parameters a,b.
  // 'a' in [0, 2*PI] corresponds to angle theta around the cylinder
  // 'b' in [0, 1] corresponds to height from the bottom
}

void boxCoordinates(struct object3D *box, double a, double b, double *x, double *y, double *z) {
  // Return in (x,y,z) the coordinates of a point on the plane given by the 2 parameters a,b.
}

void planeSample(struct object3D *plane, double *x, double *y, double *z) {
  // Returns the 3D coordinates (x,y,z) of a randomly sampled point on the plane
  // Sampling should be uniform, meaning there should be an equal chance of getting
  // any spot on the plane

  struct point3D p;
  p.px = 2 * (drand48() - 0.5);
  p.py = 2 * (drand48() - 0.5);
  p.pz = 0;
  p.pw = 1;
  matVecMult(plane->T, &p);
  *x = p.px;
  *y = p.py;
  *z = p.pz;
}

void sphereSample(struct object3D *sphere, double *x, double *y, double *z) {
  // Returns the 3D coordinates (x,y,z) of a randomly sampled point on the sphere
  // Sampling should be uniform - note that this is tricky for a sphere, do some
  // research and document in your report what method is used to do this, along
  // with a reference to your source.
}

void cylSample(struct object3D *cyl, double *x, double *y, double *z) {
  // Returns the 3D coordinates (x,y,z) of a randomly sampled point on the cylinder
  // Sampling should be uniform over the cylinder.
}

void boxSample(struct object3D *box, double *x, double *y, double *z) {

}


/////////////////////////////////
// Texture mapping functions
/////////////////////////////////
void loadTexture(struct object3D *o, const char *filename, int type, struct textureNode **t_list)
{
 // Load a texture or normal map image from file and assign it to the
 // specified object. 
 // type:   1  ->  Texture map  (RGB, .ppm)
 //         2  ->  Normal map   (RGB, .ppm)
 //         3  ->  Alpha map    (grayscale, .pgm)
 // Stores loaded images in a linked list to avoid replication
 struct image *im;
 struct textureNode *p;
 
 if (o!=NULL) {
  // Check current linked list
  p=*(t_list);
  while (p!=NULL) {
    if (strcmp(&p->name[0],filename)==0) {
      // Found image already on the list
      if (type==1) o->texImg=p->im;
      else if (type==2) o->normalMap=p->im;
      else o->alphaMap=p->im;
      return;
    }
    p=p->next;
  }

  // Load this texture image 
  if (type==1||type==2)
   im=readPPMimage(filename);
  else if (type==3)
   im=readPGMimage(filename);

  // Insert it into the texture list
  if (im!=NULL) {
   p=(struct textureNode *)calloc(1,sizeof(struct textureNode));
   strcpy(&p->name[0],filename);
   p->type=type;
   p->im=im;
   p->next=NULL; 
   // Insert into linked list
   if ((*(t_list))==NULL)
    *(t_list)=p;
   else
   {
    p->next=(*(t_list))->next;
    (*(t_list))->next=p;
   }
   // Assign to object
   if (type==1) o->texImg=im;
   else if (type==2) o->normalMap=im;
   else o->alphaMap=im;
  }
 
 }  // end if (o != NULL)
}


void texMap(struct image *img, double a, double b, double *R, double *G, double *B) {
  //Function to determine the colour of a textured object at
  //the normalized texture coordinates (a,b).
  //a and b are texture coordinates in [0 1].
  //img is a pointer to the image structure holding the texture for
  // a given object.
  //The colour is returned in R, G, B. Uses bi-linear interpolation
  //to determine texture colour.

  double *cData = (double *) img->rgbdata;
  int offset;

  struct colourRGB col;
  col.R = 0.0;
  col.G = 0.0;
  col.B = 0.0;

  //Determine the points for interpolation
  int x0 = (img->sx * a);
  int y0 = (img->sy * b);
  int x1 = x0 + 1;
  int y1 = y1 + 1;
  
  //Makes sure we don't go off the image.
  if (x1 > img->sx) { x1 = img->sx; x0 = x1 - 1; }
  if (y1 > img->sy) { y1 = img->sy; y0 = y1 - 1; }
  if (x0 < 0) { x1 = 1; x0 = 0; }
  if (y0 < 0) { y1 = 1; y0 = 0; }

  offset = (y0 * img->sx * 3) + (x0 * 3);
  col.R += *(cData + offset + 0);
  col.G += *(cData + offset + 1);
  col.B += *(cData + offset + 2);

  offset = (y1 * img->sx * 3) + (x0 * 3);
  col.R += *(cData + offset + 0);
  col.G += *(cData + offset + 1);
  col.B += *(cData + offset + 2);

  offset = (y0 * img->sx * 3) + (x1 * 3);
  col.R += *(cData + offset + 0);
  col.G += *(cData + offset + 1);
  col.B += *(cData + offset + 2);

  offset = (y1 * img->sx * 3) + (x1 * 3);
  col.R += *(cData + offset + 0);
  col.G += *(cData + offset + 1);
  col.B += *(cData + offset + 2);

  col.R /= 4;
  col.G /= 4;
  col.B /= 4; 

  *(R) = col.R;
  *(G) = col.G;
  *(B) = col.B;
}

void alphaMap(struct image *img, double a, double b, double *alpha) {
  // Just like texture map but returns the alpha value at a,b,
  // notice that alpha maps are single layer grayscale images, hence
  // the separate function.
 
  *(alpha)=1;	// Returns 1 which means fully opaque. Replace
  return;	// with your code if implementing alpha maps.
}


/////////////////////////////
// Light sources
/////////////////////////////
void insertPLS(struct pointLS *l, struct pointLS **list) {
  if (l==NULL) return;
  // Inserts a light source into the list of light sources
  if (*(list)==NULL) {
    *(list)=l;
    (*(list))->next=NULL;
  } else {
    l->next=(*(list))->next;
    (*(list))->next=l;
  }
}

void addAreaLight(double sx, double sy, double nx, double ny, double nz,\
                  double tx, double ty, double tz,\
                  double r, double g, double b, struct object3D **o_list, struct pointLS **l_list) {
  //This function sets up and inserts a rectangular area light source
  //with size (sx, sy)
  //orientation given by the normal vector (nx, ny, nz)
  //centered at (tx, ty, tz)
  //consisting of (N) point light sources (uniformly sampled)
  //and with colour/intensity (r,g,b) 
  //Note that the light source must be visible as a uniformly colored rectangle which
  //casts no shadows. If you require a lightsource to shade another, you must
  //make it into a proper solid box with a back and sides of non-light-emitting
  //material

  struct object3D *plane=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!plane) {
    fprintf(stderr,"Unable to allocate new planar light source, out of memory!\n");
  } else {
    plane->hasVolume=0;
    plane->alb.ra=1.0;
    plane->alb.rd=0.0;
    plane->alb.rs=0.0;
    plane->alb.rg=0.0;
    plane->col.R=r;
    plane->col.G=g;
    plane->col.B=b;
    plane->alpha=1.0;
    plane->r_index=1.0;
    plane->shinyness=1.0;
    plane->intersect=&planeIntersect;
    plane->surfaceCoords=&planeCoordinates;
    plane->randomPoint=&planeSample;
    plane->texImg=NULL;
    plane->photonMap=NULL;
    plane->normalMap=NULL;
    memcpy(&plane->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&plane->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    plane->textureMap=&texMap;
    plane->frontAndBack=1;
    plane->photonMapped=0;
    plane->normalMapped=0;
    plane->isCSG=0;
    plane->isLightSource=1;
    plane->CSGnext=NULL;
    plane->next=NULL;

    double theta, phi, radius;
    radius = sqrt((nx * nx) + (ny * ny) + (nz * nz));
    theta = acos(nz / radius);
    phi = atan2(ny, nx);

    Scale(plane, sx, sy, 1);
    RotateY(plane, theta);
    RotateZ(plane, phi);
    Translate(plane, tx, ty, tz);
    invert(&plane->T[0][0], &plane->Tinv[0][0]);
    insertObject(plane, o_list);

  }
}

void addPlanarLight(double sx, double sy, double rx, double ry, double rz,\
                  double tx, double ty, double tz,\
                  double r, double g, double b,\
                  struct object3D **o_list, struct pointLS **l_list, struct textureNode **t_list, const char *filename) {
  //This function sets up and inserts a rectangular area light source
  //with size (sx, sy)
  //rotated around z, y, x axis by rz, ry, rx
  //translated by (tx, ty, tz)
  //and with colour/intensity (r,g,b) 
  //Note that the light source must be visible as a uniformly colored rectangle which
  //casts no shadows. If you require a lightsource to shade another, you must
  //make it into a proper solid box with a back and sides of non-light-emitting
  //material

  struct object3D *plane=(struct object3D *)calloc(1,sizeof(struct object3D));

  if (!plane) {
    fprintf(stderr,"Unable to allocate new planar light source, out of memory!\n");
  } else {
    plane->hasVolume=0;
    plane->alb.ra=1.0;
    plane->alb.rd=1.0;
    plane->alb.rs=1.0;
    plane->alb.rg=0.0;
    plane->col.R=r;
    plane->col.G=g;
    plane->col.B=b;
    plane->alpha=1.0;
    plane->r_index=1.0;
    plane->shinyness=1.0;
    plane->intersect=&planeIntersect;
    plane->surfaceCoords=&planeCoordinates;
    plane->randomPoint=&planeSample;
    plane->texImg=NULL;
    plane->photonMap=NULL;
    plane->normalMap=NULL;
    memcpy(&plane->T[0][0],&eye4x4[0][0],16*sizeof(double));
    memcpy(&plane->Tinv[0][0],&eye4x4[0][0],16*sizeof(double));
    plane->textureMap=&texMap;
    plane->frontAndBack=1;
    plane->photonMapped=0;
    plane->normalMapped=0;
    plane->isCSG=0;
    plane->isLightSource=1;
    plane->CSGnext=NULL;
    plane->next=NULL;

    Scale(plane, sx, sy, 1);
    if (rz != 0.0) { RotateZ(plane, rz); }
    if (ry != 0.0) { RotateY(plane, ry); }
    if (rx != 0.0) { RotateX(plane, rx); }
    Translate(plane, tx, ty, tz);
    invert(&plane->T[0][0], &plane->Tinv[0][0]);
    loadTexture(plane, filename, 1, t_list);
    insertObject(plane, o_list);

  }
}

///////////////////////////////////
// Geometric transformation section
///////////////////////////////////

void invert(double *T, double *Tinv) {
  // Computes the inverse of transformation matrix T.
  // the result is returned in Tinv.

  double *U, *s, *V, *rv1;
  int singFlag, i;

  // Invert the affine transform
  U=NULL;
  s=NULL;
  V=NULL;
  rv1=NULL;
  singFlag=0;

  SVD(T,4,4,&U,&s,&V,&rv1);
  if (U==NULL||s==NULL||V==NULL) {
    fprintf(stderr,"Error: Matrix not invertible for this object, returning identity\n");
    memcpy(Tinv,eye4x4,16*sizeof(double));
    return;
  }

  // Check for singular matrices...
  for (i=0;i<4;i++) {
    if (*(s+i)<1e-9) {
      singFlag=1;
    }
  }

  if (singFlag) {
    fprintf(stderr,"Error: Transformation matrix is singular, returning identity\n");
    memcpy(Tinv,eye4x4,16*sizeof(double));
    return;
  }

  // Compute and store inverse matrix
  InvertMatrix(U,s,V,4,Tinv);

  free(U);
  free(s);
  free(V);
}

void RotateXMat(double T[4][4], double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // X axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=1.0;
  R[1][1]=cos(theta);
  R[1][2]=-sin(theta);
  R[2][1]=sin(theta);
  R[2][2]=cos(theta);
  R[3][3]=1.0;

  matMult(R,T);
}

void RotateX(struct object3D *o, double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // X axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=1.0;
  R[1][1]=cos(theta);
  R[1][2]=-sin(theta);
  R[2][1]=sin(theta);
  R[2][2]=cos(theta);
  R[3][3]=1.0;

  matMult(R,o->T);
}

void RotateYMat(double T[4][4], double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // Y axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=cos(theta);
  R[0][2]=sin(theta);
  R[1][1]=1.0;
  R[2][0]=-sin(theta);
  R[2][2]=cos(theta);
  R[3][3]=1.0;

  matMult(R,T);
}

void RotateY(struct object3D *o, double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // Y axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=cos(theta);
  R[0][2]=sin(theta);
  R[1][1]=1.0;
  R[2][0]=-sin(theta);
  R[2][2]=cos(theta);
  R[3][3]=1.0;

  matMult(R,o->T);
}

void RotateZMat(double T[4][4], double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // Z axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=cos(theta);
  R[0][1]=-sin(theta);
  R[1][0]=sin(theta);
  R[1][1]=cos(theta);
  R[2][2]=1.0;
  R[3][3]=1.0;

  matMult(R,T);
}

void RotateZ(struct object3D *o, double theta) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that rotates the object theta *RADIANS* around the
  // Z axis.

  double R[4][4];
  memset(&R[0][0],0,16*sizeof(double));

  R[0][0]=cos(theta);
  R[0][1]=-sin(theta);
  R[1][0]=sin(theta);
  R[1][1]=cos(theta);
  R[2][2]=1.0;
  R[3][3]=1.0;

  matMult(R,o->T);
}

void TranslateMat(double T[4][4], double tx, double ty, double tz) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that translates the object by the specified amounts.

  double tr[4][4];
  memset(&tr[0][0],0,16*sizeof(double));

  tr[0][0]=1.0;
  tr[1][1]=1.0;
  tr[2][2]=1.0;
  tr[0][3]=tx;
  tr[1][3]=ty;
  tr[2][3]=tz;
  tr[3][3]=1.0;

  matMult(tr,T);
}

void Translate(struct object3D *o, double tx, double ty, double tz) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that translates the object by the specified amounts.

  double tr[4][4];
  memset(&tr[0][0],0,16*sizeof(double));

  tr[0][0]=1.0;
  tr[1][1]=1.0;
  tr[2][2]=1.0;
  tr[0][3]=tx;
  tr[1][3]=ty;
  tr[2][3]=tz;
  tr[3][3]=1.0;

  matMult(tr,o->T);
}

void ScaleMat(double T[4][4], double sx, double sy, double sz) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that scales the object as indicated.

  double S[4][4];
  memset(&S[0][0],0,16*sizeof(double));

  S[0][0]=sx;
  S[1][1]=sy;
  S[2][2]=sz;
  S[3][3]=1.0;

  matMult(S,T);
}

void Scale(struct object3D *o, double sx, double sy, double sz) {
  // Multiply the current object transformation matrix T in object o
  // by a matrix that scales the object as indicated.

  double S[4][4];
  memset(&S[0][0],0,16*sizeof(double));

  S[0][0]=sx;
  S[1][1]=sy;
  S[2][2]=sz;
  S[3][3]=1.0;

  matMult(S,o->T);
}

void printmatrix(double mat[4][4]) {
  fprintf(stderr,"Matrix contains:\n");
  fprintf(stderr,"%f %f %f %f\n",mat[0][0],mat[0][1],mat[0][2],mat[0][3]);
  fprintf(stderr,"%f %f %f %f\n",mat[1][0],mat[1][1],mat[1][2],mat[1][3]);
  fprintf(stderr,"%f %f %f %f\n",mat[2][0],mat[2][1],mat[2][2],mat[2][3]);
  fprintf(stderr,"%f %f %f %f\n",mat[3][0],mat[3][1],mat[3][2],mat[3][3]);
}

/////////////////////////////////////////
// Camera and view setup
/////////////////////////////////////////
struct view *setupView(struct point3D *e, struct point3D *g, struct point3D *up, double f, double wl, double wt, double ww, double wh) {
  //This function sets up the camera axes and viewing direction as discussed in the
  //lecture notes.
  //e - Camera center
  //g - Gaze direction
  //up - Up vector
  //fov - Field of view in degrees
  //f - focal length

  struct view *c;
  struct point3D *u, *v;

  u=v=NULL;

  // Allocate space for the camera structure
  c=(struct view *)calloc(1,sizeof(struct view));
  if (c==NULL) {
    fprintf(stderr,"Out of memory setting up camera model!\n");
    return(NULL);
  }

  // Set up camera center and axes
  c->e.px=e->px;		// Copy camera center location, note we must make sure
  c->e.py=e->py;		// the camera center provided to this function has pw=1
  c->e.pz=e->pz;
  c->e.pw=1;

  // Set up w vector (camera's Z axis). w=-g/||g||
  c->w.px=-g->px;
  c->w.py=-g->py;
  c->w.pz=-g->pz;
  c->w.pw=1;
  normalize(&c->w);

  // Set up the horizontal direction, which must be perpenticular to w and up
  u=cross(&c->w, up);
  normalize(u);
  c->u.px=u->px;
  c->u.py=u->py;
  c->u.pz=u->pz;
  c->u.pw=1;

  // Set up the remaining direction, v=(u x w)  - Mind the signs
  v=cross(&c->u, &c->w);
  normalize(v);
  c->v.px=v->px;
  c->v.py=v->py;
  c->v.pz=v->pz;
  c->v.pw=1;

  // Copy focal length and window size parameters
  c->f=f;
  c->wl=wl;
  c->wt=wt;
  c->wwidth=ww;
  c->wheight=wh;

  // Set up coordinate conversion matrices
  // Camera2World matrix (M_cw in the notes)
  // Mind the indexing convention [row][col]
  c->C2W[0][0]=c->u.px;
  c->C2W[1][0]=c->u.py;
  c->C2W[2][0]=c->u.pz;
  c->C2W[3][0]=0;

  c->C2W[0][1]=c->v.px;
  c->C2W[1][1]=c->v.py;
  c->C2W[2][1]=c->v.pz;
  c->C2W[3][1]=0;

  c->C2W[0][2]=c->w.px;
  c->C2W[1][2]=c->w.py;
  c->C2W[2][2]=c->w.pz;
  c->C2W[3][2]=0;

  c->C2W[0][3]=c->e.px;
  c->C2W[1][3]=c->e.py;
  c->C2W[2][3]=c->e.pz;
  c->C2W[3][3]=1;

  // World2Camera matrix (M_wc in the notes)
  // Mind the indexing convention [row][col]
  c->W2C[0][0]=c->u.px;
  c->W2C[1][0]=c->v.px;
  c->W2C[2][0]=c->w.px;
  c->W2C[3][0]=0;

  c->W2C[0][1]=c->u.py;
  c->W2C[1][1]=c->v.py;
  c->W2C[2][1]=c->w.py;
  c->W2C[3][1]=0;

  c->W2C[0][2]=c->u.pz;
  c->W2C[1][2]=c->v.pz;
  c->W2C[2][2]=c->w.pz;
  c->W2C[3][2]=0;

  c->W2C[0][3]=-dot(&c->u,&c->e);
  c->W2C[1][3]=-dot(&c->v,&c->e);
  c->W2C[2][3]=-dot(&c->w,&c->e);
  c->W2C[3][3]=1;

  free(u);
  free(v);
  return(c);
}

/////////////////////////////////////////
// Image I/O section
/////////////////////////////////////////
struct image *readPPMimage(const char *filename) {
  // Reads an image from a .ppm file. A .ppm file is a very simple image representation
  // format with a text header followed by the binary RGB data at 24bits per pixel.
  // The header has the following form:
  //
  // P6
  // # One or more comment lines preceded by '#'
  // 340 200
  // 255
  //
  // The first line 'P6' is the .ppm format identifier, this is followed by one or more
  // lines with comments, typically used to inidicate which program generated the
  // .ppm file.
  // After the comments, a line with two integer values specifies the image resolution
  // as number of pixels in x and number of pixels in y.
  // The final line of the header stores the maximum value for pixels in the image,
  // usually 255.
  // After this last header line, binary data stores the RGB values for each pixel
  // in row-major order. Each pixel requires 3 bytes ordered R, G, and B.
  //
  // NOTE: Windows file handling is rather crotchetty. You may have to change the
  //       way this file is accessed if the images are being corrupted on read
  //       on Windows.
  //
  // readPPMdata converts the image colour information to floating point. This is so that
  // the texture mapping function doesn't have to do the conversion every time
  // it is asked to return the colour at a specific location.
  //

  FILE *f;
  struct image *im;
  char line[1024];
  int sizx,sizy;
  int i;
  unsigned char *tmp;
  double *fRGB;

  im=(struct image *)calloc(1,sizeof(struct image));
  if (im!=NULL) {
    im->rgbdata=NULL;
    f=fopen(filename,"rb+");
    if (f==NULL) {
      fprintf(stderr,"Unable to open file %s for reading, please check name and path\n",filename);
      free(im);
      return(NULL);
    }
    fgets(&line[0],1000,f);
    if (strcmp(&line[0],"P6\n")!=0) {
      fprintf(stderr,"Wrong file format, not a .ppm file or header end-of-line characters missing\n");
      free(im);
      fclose(f);
      return(NULL);
    }
    fprintf(stderr,"%s\n",line);
    // Skip over comments
    fgets(&line[0],511,f);
    while (line[0]=='#') {
      fprintf(stderr,"%s",line);
      fgets(&line[0],511,f);
    }
    sscanf(&line[0],"%d %d\n",&sizx,&sizy);           // Read file size
    fprintf(stderr,"nx=%d, ny=%d\n\n",sizx,sizy);
    im->sx=sizx;
    im->sy=sizy;

    fgets(&line[0],9,f);  	                // Read the remaining header line
    tmp=(unsigned char *)calloc(sizx*sizy*3,sizeof(unsigned char));
    fRGB=(double *)calloc(sizx*sizy*3,sizeof(double));
    if (tmp==NULL||fRGB==NULL) {
      fprintf(stderr,"Out of memory allocating space for image\n");
      free(im);
      fclose(f);
      return(NULL);
    }

    fread(tmp,sizx*sizy*3*sizeof(unsigned char),1,f);
    fclose(f);

    // Conversion to floating point
    for (i=0; i<sizx*sizy*3; i++) {
      *(fRGB+i)=((double)*(tmp+i))/255.0;
    }

    free(tmp);
    im->rgbdata=(void *)fRGB;

    return(im);
  }

  fprintf(stderr,"Unable to allocate memory for image structure\n");
  return(NULL);
}

struct image *readPGMimage(const char *filename) {
  // Just like readPPMimage() except it is used to load grayscale alpha maps. In
  // alpha maps, a value of 255 corresponds to alpha=1 (fully opaque) and 0 
  // correspondst to alpha=0 (fully transparent).
  // A .pgm header of the following form is expected:
  //
  // P5
  // # One or more comment lines preceded by '#'
  // 340 200
  // 255
  //
  // readPGMdata converts the image grayscale data to double floating point in [0,1]. 

  FILE *f;
  struct image *im;
  char line[1024];
  int sizx,sizy;
  int i;
  unsigned char *tmp;
  double *fRGB;

  im=(struct image *)calloc(1,sizeof(struct image));
  if (im!=NULL) {
    im->rgbdata=NULL;
    f=fopen(filename,"rb+");
    if (f==NULL) {
      fprintf(stderr,"Unable to open file %s for reading, please check name and path\n",filename);
      free(im);
      return(NULL);
    }
    fgets(&line[0],1000,f);
    if (strcmp(&line[0],"P5\n")!=0) {
      fprintf(stderr,"Wrong file format, not a .pgm file or header end-of-line characters missing\n");
      free(im);
      fclose(f);
      return(NULL);
    }
    // Skip over comments
    fgets(&line[0],511,f);
    while (line[0]=='#'){
      fgets(&line[0],511,f);
    }
    sscanf(&line[0],"%d %d\n",&sizx,&sizy);           // Read file size
    im->sx=sizx;
    im->sy=sizy;

    fgets(&line[0],9,f);  	                // Read the remaining header line
    tmp=(unsigned char *)calloc(sizx*sizy,sizeof(unsigned char));
    fRGB=(double *)calloc(sizx*sizy,sizeof(double));
    if (tmp==NULL||fRGB==NULL) {
      fprintf(stderr,"Out of memory allocating space for image\n");
      free(im);
      fclose(f);
      return(NULL);
    }

    fread(tmp,sizx*sizy*sizeof(unsigned char),1,f);
    fclose(f);

    // Conversion to double floating point
    for (i=0; i<sizx*sizy; i++) {
      *(fRGB+i)=((double)*(tmp+i))/255.0;
    }
    free(tmp);
    im->rgbdata=(void *)fRGB;

    return(im);
  }

  fprintf(stderr,"Unable to allocate memory for image structure\n");
  return(NULL);
}

struct image *newImage(int size_x, int size_y) {
  // Allocates and returns a new image with all zeros. Assumes 24 bit per pixel,
  // unsigned char array.
  struct image *im;

  im=(struct image *)calloc(1,sizeof(struct image));
  if (im!=NULL) {
    im->rgbdata=NULL;
    im->sx=size_x;
    im->sy=size_y;
    im->rgbdata=(void *)calloc(size_x*size_y*3,sizeof(unsigned char));
    if (im->rgbdata!=NULL) {
      return(im);
    }
  }
  fprintf(stderr,"Unable to allocate memory for new image\n");
  return(NULL);
}

void imageOutput(struct image *im, const char *filename) {
  // Writes out a .ppm file from the image data contained in 'im'.
  // Note that Windows typically doesn't know how to open .ppm
  // images. Use Gimp or any other seious image processing
  // software to display .ppm images.
  // Also, note that because of Windows file format management,
  // you may have to modify this file to get image output on
  // Windows machines to work properly.
  //
  // Assumes a 24 bit per pixel image stored as unsigned chars
  //

  FILE *f;

  if (im!=NULL) {
    if (im->rgbdata!=NULL) {
      f=fopen(filename,"wb+");
      if (f==NULL) {
        fprintf(stderr,"Unable to open file %s for output! No image written\n",filename);
        return;
      }
      fprintf(f,"P6\n");
      fprintf(f,"# Output from RayTracer.c\n");
      fprintf(f,"%d %d\n",im->sx,im->sy);
      fprintf(f,"255\n");
      fwrite((unsigned char *)im->rgbdata,im->sx*im->sy*3*sizeof(unsigned char),1,f);
      fclose(f);
      return;
    }
  }
  fprintf(stderr,"imageOutput(): Specified image is empty. Nothing output\n");
}

void deleteImage(struct image *im) {
  // De-allocates memory reserved for the image stored in 'im'
  if (im!=NULL) {
    if (im->rgbdata!=NULL) { 
      free(im->rgbdata);
    }
    free(im);
  }
}

void cleanup(struct object3D *o_list, struct pointLS *l_list, struct textureNode *t_list) {
  // De-allocates memory reserved for the object list and the point light source
  // list. Note that *YOU* must de-allocate any memory reserved for images
  // rendered by the raytracer.
  struct object3D *p, *q;
  struct pointLS *r, *s;
  struct textureNode *t, *u;

  p=o_list;		// De-allocate all memory from objects in the list
  while(p!=NULL) {
    q=p->next;
    if (p->photonMap!=NULL) {
      if (p->photonMap->rgbdata!=NULL) {
        free(p->photonMap->rgbdata);
      }
      free(p->photonMap);
    }
    free(p);
    p=q;
  }

  r=l_list;		// Delete light source list
  while(r!=NULL) {
    s=r->next;
    free(r);
    r=s;
  }

  t=t_list;		// Delete texture Images
  while(t!=NULL) {
    u=t->next;
    if (t->im->rgbdata!=NULL) {
      free(t->im->rgbdata);
    }
    free(t->im);
    free(t);
    t=u;
  }
}

