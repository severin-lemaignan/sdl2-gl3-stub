#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <assimp/matrix4x4.h>
#include <glm/glm.hpp>

/*
  Prints out an ASSIMP matrix
  */
void printai(const aiMatrix4x4& mat) {
    std::cout << mat.a1 << "\t" << mat.a2 << "\t" << mat.a3 << "\t" << mat.a4 << std::endl;
    std::cout << mat.b1 << "\t" << mat.b2 << "\t" << mat.b3 << "\t" << mat.b4 << std::endl;
    std::cout << mat.c1 << "\t" << mat.c2 << "\t" << mat.c3 << "\t" << mat.c4 << std::endl;
    std::cout << mat.d1 << "\t" << mat.d2 << "\t" << mat.d3 << "\t" << mat.d4 << std::endl;
}

/*
  Prints out a GLM matrix
*/
void printglm(const glm::mat4& mat) {
    std::cout << mat[0][0] << "\t" << mat[1][0] << "\t" << mat[2][0] << "\t" << mat[3][0] << std::endl;
    std::cout << mat[0][1] << "\t" << mat[1][1] << "\t" << mat[2][1] << "\t" << mat[3][1] << std::endl;
    std::cout << mat[0][2] << "\t" << mat[1][2] << "\t" << mat[2][2] << "\t" << mat[3][2] << std::endl;
    std::cout << mat[0][3] << "\t" << mat[1][3] << "\t" << mat[2][3] << "\t" << mat[3][3] << std::endl;
}


#endif // HELPERS_H
