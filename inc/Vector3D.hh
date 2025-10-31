#ifndef VECTOR3D_HH
#define VECTOR3D_HH

#include "geomVector.hh"

/*!
 * \file
 * \brief Deklaracja instacji szablonu geom::Vector
 */

 /*!
  * \brief Instacja szablonu geom::Vector<typename,int> dla przestrzeni 3D.
  */
 typedef geom::Vector<double,3>  Vector3D;

    inline double deg2rad(double d) { return d * M_PI / 180.0; }
    inline bool IsClose(const Vector3D &a, const Vector3D &b, double eps = 0.001) {
        for (int i = 0; i < 3; ++i)
            if (fabs(a[i] - b[i]) > eps) return false;
        return true;
    }
    inline Vector3D RotateVector(const Vector3D &v, const Vector3D &rot_deg)
    {
        Vector3D res = v;

        // Rx
        double phi = deg2rad(rot_deg[0]);
        double cx = cos(phi), sx = sin(phi);
        double y1 = cx * res[1] - sx * res[2];
        double z1 = sx * res[1] + cx * res[2];
        res[1] = y1; res[2] = z1;

        // Ry
        double theta = deg2rad(rot_deg[1]);
        double cy = cos(theta), sy = sin(theta);
        double x2 = cy * res[0] + sy * res[2];
        double z2 = -sy * res[0] + cy * res[2];
        res[0] = x2; res[2] = z2;

        // Rz
        double psi = deg2rad(rot_deg[2]);
        double cz = cos(psi), sz = sin(psi);
        double x3 = cz * res[0] - sz * res[1];
        double y3 = sz * res[0] + cz * res[1];
        res[0] = x3; res[1] = y3;

        return res;
    }
    inline Vector3D normal_multi(const Vector3D &v1, const Vector3D &v2){
        Vector3D res;
        res[0] = v1[0] * v2[0];
        res[1] = v1[1] * v2[1];
        res[2] = v1[2] * v2[2];
        return res;
    }


#endif
