#include <stdio.h>
#include <math.h>
#define PI 3.1415926535897932384626433832795

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/*  Vincenty Inverse Solution of Geodesics on the Ellipsoid (c) Chris Veness 2002-2009            */
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

/*
 * Calculate geodesic distance (in m) between two points specified by latitude/longitude 
 * (in numeric degrees) using Vincenty inverse formula for ellipsoids
 */
double distVincenty(double lat1,double  lon1,double  lat2,double  lon2) 
{
  double a = 6378137, b = 6356752.3142,  f = 1/298.257223563;  // WGS-84 ellipsiod
  double L = (lon2-lon1)*PI/180;
  double U1 = atan((1-f) * tan(lat1*PI/180));
  double U2 = atan((1-f) * tan(lat2*PI/180));
  double sinU1 = sin(U1), cosU1 = cos(U1);
  double sinU2 = sin(U2), cosU2 = cos(U2);
  
  double lambda = L, lambdaP, iterLimit = 400;
  double sigma,sinAlpha,cosSqAlpha,cos2SigmaM,sinSigma,cosSigma;
  do {
    double sinLambda = sin(lambda), cosLambda = cos(lambda);
    sinSigma = sqrt((cosU2*sinLambda) * (cosU2*sinLambda) + 
      (cosU1*sinU2-sinU1*cosU2*cosLambda) * (cosU1*sinU2-sinU1*cosU2*cosLambda));
    if (sinSigma==0) return 0;  // co-incident points
    cosSigma = sinU1*sinU2 + cosU1*cosU2*cosLambda;
    sigma = atan2(sinSigma, cosSigma);
    sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
    cosSqAlpha = 1 - sinAlpha*sinAlpha;
    cos2SigmaM;
	
    //if (isNaN(cos2SigmaM)) cos2SigmaM = 0;  // equatorial line: cosSqAlpha=0 (§6)
	if (cosSqAlpha)
		cos2SigmaM= cosSigma - 2*sinU1*sinU2/cosSqAlpha;
	else cos2SigmaM = 0;

    double C = f/16*cosSqAlpha*(4+f*(4-3*cosSqAlpha));
    lambdaP = lambda;
    lambda = L + (1-C) * f * sinAlpha *
      (sigma + C*sinSigma*(cos2SigmaM+C*cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)));
  } while ((fabs(lambda-lambdaP) > 1e-12) && (--iterLimit>0));

  if (iterLimit==0) return -77777777777777;  // formula failed to converge

  double uSq = cosSqAlpha * (a*a - b*b) / (b*b);
  double A = 1 + uSq/16384*(4096+uSq*(-768+uSq*(320-175*uSq)));
  double B = uSq/1024 * (256+uSq*(-128+uSq*(74-47*uSq)));
  double deltaSigma = B*sinSigma*(cos2SigmaM+B/4*(cosSigma*(-1+2*cos2SigmaM*cos2SigmaM)-
    B/6*cos2SigmaM*(-3+4*sinSigma*sinSigma)*(-3+4*cos2SigmaM*cos2SigmaM)));
  double s = b*A*(sigma-deltaSigma);
  
//  s = s.toFixed(3); // round to 1mm precision
  return s;
}

double distancia2(double lat1,double  lon1,double  lat2,double  lon2)
{
	double d;
	double R=6371000;
	lat1*=(PI/180);
	lat2*=(PI/180);
	lon1*=(PI/180);
	lon2*=(PI/180);
	d = acos(sin(lat1)*sin(lat2) + cos(lat1)*cos(lat2)*cos(lon2-lon1))*R;
	return d;
}


void main()
{
	double distancia;
	distancia=distVincenty(41.369530,  -3.201680,41.294000,  -3.121510);
	distancia=distancia2(  41.369530,  -3.201680,41.294000,  -3.121510);
	distancia=1;
}