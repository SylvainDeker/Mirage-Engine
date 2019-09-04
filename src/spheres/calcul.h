#ifndef CALCULL_H
#define CALCULL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "subdivide.hpp"

float surfacetriangle2(const glm::vec3 &a,const glm::vec3 &b,const glm::vec3 &c){

  glm::vec3 v1= b-a;
  glm::vec3 v2= c-a;
  return glm::abs(glm::length(glm::cross(v1,v2))) / 2.f;

}

glm::vec3 getCoord(const size_t index_vertex,std::vector<float> &_vertices){

  return glm::vec3(_vertices[index_vertex*3+0],_vertices[index_vertex*3+1],_vertices[index_vertex*3+2]);
}


void uvsphere(size_t slices){

    std::vector<float> _vertices;
    std::vector<float> _normals;
    std::vector<size_t> _indices;

    size_t scale_lat = slices;
    size_t scale_lon = scale_lat *2;
    float theta = 0;
    float phi = 0;
    float r = 1.f;
    float x,y,z;
    for(size_t i = 0; i < scale_lon; i++)
    {
        theta =  (float(i)*glm::pi<float>())*2/scale_lon;

        for(size_t j = 0; j < scale_lat; j++)
        {


            phi = (float(j+1)*glm::pi<float>())/(scale_lat+1);
            x = r * glm::sin(theta)*glm::sin(phi);
            y = r * glm::cos(phi);
            z = r * glm::cos(theta)*glm::sin(phi);

            _vertices.push_back(x);
            _vertices.push_back(y);
            _vertices.push_back(z);
            // printf("%f\t%f\t%f\n",x,y,z);

            _normals.push_back(x/r);
            _normals.push_back(y/r);
            _normals.push_back(z/r);

            if(j!=scale_lat-1){
                _indices.push_back((i*scale_lat+(j))%(scale_lat*scale_lon));
                _indices.push_back((i*scale_lat+(j)+1)%(scale_lat*scale_lon));
                _indices.push_back(((i+1)*scale_lat+(j))%(scale_lat*scale_lon));

                _indices.push_back(((i+1)*scale_lat+(j+1))%(scale_lat*scale_lon));
                _indices.push_back((i*scale_lat+j+1)%(scale_lat*scale_lon));
                _indices.push_back(((i+1)*scale_lat+(j))%(scale_lat*scale_lon));


            }
        }
    }

    x = 0;
    y = r;
    z = 0;
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
    _normals.push_back(0);
    _normals.push_back(1);
    _normals.push_back(0);

    for(size_t i = 0; i < scale_lon; i++)
    {
        _indices.push_back(scale_lon*scale_lat);
        _indices.push_back(i*scale_lat);
        _indices.push_back( ((i+1)*scale_lat ) % (scale_lon*scale_lat)  );
    }


    x = 0;
    y = -r;
    z = 0;
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
    _normals.push_back(0);
    _normals.push_back(-1);
    _normals.push_back(0);


    for(size_t i = 0; i < scale_lon; i++)
    {
        _indices.push_back(scale_lon*scale_lat+1);
        _indices.push_back(i*scale_lat+scale_lat-1);
        _indices.push_back( ((i+1)*scale_lat +scale_lat-1 ) % (scale_lon*scale_lat)  );
    }



    glm::vec3 pta,ptb,ptc;
    float sum =0;
    for (size_t i = 0; i < _indices.size(); i+=3) {
       pta = getCoord(_indices[i+0],_vertices);
       ptb = getCoord(_indices[i+1],_vertices);
       ptc = getCoord(_indices[i+2],_vertices);
       sum += surfacetriangle2(pta,ptb,ptc);
    }

    std::cout << 4*glm::pi<float>()*r*r << '\t';
    std::cout << _indices.size()/3 << '\t' << sum << '\n';
}


void calculuvsphere(size_t max){
  for (size_t i = 0; i < max; i++) {
    uvsphere(i);
  }
}



void icosphere(size_t nbsub){
  float w = 0.525731f;
  float l = w * (1.f+float(glm::sqrt(5.f)))/2.f;
  float dist = glm::sqrt(w*w+l*l+0*0);

  std::vector<GLfloat> _vertices;
  std::vector<GLfloat> _normals;
  std::vector<GLuint> _indices;

  _vertices = { -w,0.f,l,
                 w,0.f,l,
                -w,0.f,-l,
                 w,0.f,-l,
                 0.f,l,w,
                 0.f,l,-w,
                 0.f,-l,w,
                 0.f,-l,-w,
                 l,w,0.f,
                 -l,w, 0.f,
                 l,-w,0.f,
                 -l,-w, 0.f  };

  _normals = { -w/dist,0.f,l/dist,
                w/dist,0.f,l/dist,
               -w/dist,0.f,-l/dist,
               w/dist,0.f,-l/dist,
               0.f,l/dist,w/dist,
              0.f,l/dist,-w/dist,
              0.f,-l/dist,w/dist,
              0.f,-l/dist,-w/dist,
               l/dist,w/dist,0.f,
               -l/dist,w/dist, 0.f,
               l/dist,-w/dist,0.f,
               -l/dist,-w/dist, 0.f  };

  _indices = { 0,4,1,
               0,9,4,
               9,5,4,
               4,5,8,
               4,8,1,
               8,10,1,
               8,3,10,
               5,3,8,
               5,2,3,
               2,7,3,
               7,10,3,
               7,6,10,
               7,11,6,
               11,0,6,
               0,1,6,
               6,1,10,
               9,0,11,
               9,11,2,
               9,2,5,
               7,2,11 };

  for (size_t i = 0; i < nbsub; i++) {
    SubDivide sb(_vertices,_normals,_indices);
    sb.setCoef( glm::sqrt( w*w+l*l ) );
    sb.run();

  }

  glm::vec3 pta,ptb,ptc;
  float sum =0;
  for (size_t i = 0; i < _indices.size(); i+=3) {
     pta = getCoord(_indices[i+0],_vertices);
     ptb = getCoord(_indices[i+1],_vertices);
     ptc = getCoord(_indices[i+2],_vertices);
     sum += surfacetriangle2(pta,ptb,ptc);
  }

  std::cout << 4*glm::pi<float>()*dist*dist << '\t';
  std::cout << _indices.size()/3 << '\t' << sum << '\n';

}

void calculicosphere(size_t max){
  for (size_t i = 0; i < max; i++) {
    icosphere(i);
  }
}








#endif
