#include <aurora/Vector.h>
#include <aurora/Color.h>
#include <aurora/Math.h>
#include <aurora/Image.h>
#include <aurora/Matrix.h>
#include <aurora/Utility.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace aurora;
using namespace std;

struct intersection 
{
	bool hit;
	float distance;
	size_t index;
	
	intersection()
	{
		hit = false;
		distance = AURORA_INFINITY;
		index = size_t(-1);
	}
	
	intersection(bool hit, float distance, size_t index)
	{
		this->hit = hit;
		this->distance = AURORA_INFINITY;
		this->index = size_t(-1);
	}
};

struct ray
{
	Vector3 origin;
	Vector3 direction;
	
	ray() {}
	
	ray(Vector3 origin, Vector3 direction)
	{
		this->origin = origin;
		this->direction = direction;
	}
	
	Vector3 point (float t)
	{
		return origin + t*direction;
	}
	
};

enum BSDFType
{
	Light,Diffuse,Specular,None	
};

struct BSDF
{
	BSDFType type;
	Color3 color;
	
	BSDF() {}
	
	BSDF( BSDFType type, Color3 color)
	{
		this->type = type;
		this->color = color;
	}	
};

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 uv;
	
	Vertex() {}
	
	Vertex(Vector3 position, Vector3 normal, Vector2 uv)
	{
		this->position = position;
		this->normal = normal;
		this->uv = uv;
	}
};


struct shaderGlobals
{
	Vector3 point;
	Vector3 normal;
	Vector2 uv;
	Vector3 tangentU;
	Vector3 tangentV;
	Vector3 viewDirection;
	Vector3 lightDirection;
	Vector3 lightPoint;
	Vector3 lightNormal;
	
	shaderGlobals() {}
	
	shaderGlobals(Vector3 point,Vector3 normal,Vector2 uv,Vector3 tangentU,Vector3 tangentV,Vector3 viewDirection,Vector3 lightDirection,Vector3 lightPoint,Vector3 lightNormal) 
	{
		this->point = point;
        this->normal = normal;
        this->uv = uv;
        this->tangentU = tangentU;
        this->tangentV = tangentV;
        this->viewDirection = viewDirection;
        this->lightDirection = lightDirection;
        this->lightPoint = lightPoint;
        this->lightNormal = lightNormal;
	}
};


struct Triangle
{
	BSDF bsdf;
	Vertex vertices [3];
	
	Triangle() {}
	
	Triangle(BSDF bsdf, Vertex *vertices) {
		this->bsdf = bsdf;
		this->vertices[0] = vertices[0];
		this->vertices[1] = vertices[1];
		this->vertices[2] = vertices[2];
	}
	
	intersection intersects(ray Ray)
	{
		const float EPSILON = 0.0000001;
	    Vector3 vertex0 = vertices[0].position;
	    Vector3 vertex1 = vertices[1].position;
	    Vector3 vertex2 = vertices[2].position;
	    Vector3 edge1, edge2, h, s, q;
	    float a,f,u,v;
	    edge1 = vertex1 - vertex0;
	    edge2 = vertex2 - vertex0;
	    h = Ray.direction.cross(edge2);
	    a = edge1.dot(h);
	    if (abs(a) < EPSILON)
	        return intersection();    // This ray is parallel to this triangle.
	    f = 1.0/a;
	    s = Ray.origin - vertex0;
	    u = f * s.dot(h);
	    if (u < 0.0 || u > 1.0)
	        return intersection();
	    q = s.cross(edge1);
	    v = f * Ray.direction.dot(q);
	    if (v < 0.0 || u + v > 1.0)
	        return intersection();
	    // At this stage we can compute t to find out where the intersection point is on the line.
	    float t = f * edge2.dot(q);
	    if (t > EPSILON && t < 1/EPSILON) // ray intersection
	    {
	        //bool hit, float distance, size_t index
	        return intersection(true,t,-1);
	    }
	    else // This means that there is a line intersection but not a ray intersection.
        return intersection();
	}
	
	shaderGlobals calculateShaderGlobals(intersection Intersection ,ray Ray)
	{
		shaderGlobals sg;
		sg.point = Ray.point(Intersection.distance);
		return sg;
	}
	
	float surfaceArea()
	{
		return 0.0;
	}
		
};

struct Scene {
    std::vector<Triangle*> triangles;
    
    Scene();
    Scene(const std::vector<Triangle *> & triangles) {
        this->triangles = triangles;
    }
    
    bool intersects(ray Ray, intersection & Intersection) const {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle * Triangle = triangles[i];
            
            intersection temp;
            Triangle->intersects(Ray);
            
            if (temp.hit && temp.distance < Intersection.distance) {
                Intersection.hit = temp.hit;
                Intersection.distance = temp.distance;
                Intersection.index = i;
            }
        }
        
        return Intersection.hit;
    }
};

int main(int argc, char ** argv) {
    Vertex v0;
	Vertex v1;
	Vertex v2;
	
	v0.position = Vector3(0.0, 0.0, 0.0);
	v0.normal = Vector3(0.0, 0.0, 1.0);
	v0.uv = Vector2(0.0, 0.0);
	
	v1.position = Vector3(2.0, 0.0, 0.0);
	v1.normal = Vector3(0.0, 0.0, 1.0);
	v1.uv = Vector2(1.0, 0.0);
	
	v2.position = Vector3(1.0, 2.0, 0.0);
	v2.normal = Vector3(0.0, 0.0, 1.0);
	v2.uv = Vector2(0.0, 1.0);
	
	ray r0;
	
	r0.origin = Vector3(1.0, 1.0, 10.0);
	r0.direction = Vector3(0.0, 0.0, -1.0);
	
	Color3 red(1.0, 0.0, 0.0);
	BSDF * diffuse = new BSDF (BSDFType::Diffuse, red);
	Triangle* t = new Triangle (diffuse, Vector3(v0,v1,v2));
	
	vector<Triangle*> triangles = {t};
	
	Scene scene (triangles);
	
	intersection Intersection;
	
	scene.intersects(r0, Intersection); 
	
	if(Intersection.hit){
		cout<<"Ponto: " <<Intersection.distance<<endl;
	}
	else cout<<"Sem intersecao!"<<endl;
	
	delete t;
	delete diffuse;
    
	return 0;
}
