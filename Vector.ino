double angleBetweenVectors(Vector initial, Vector current)
{
  double dotProduct = (double)initial.x*(double)current.x+(double)initial.y*(double)current.y+(double)initial.z*(double)current.z;  
  double thetaRad = fabs(acos(dotProduct/(initial.magnitude*current.magnitude)));
  return thetaRad*180/PI;
}
