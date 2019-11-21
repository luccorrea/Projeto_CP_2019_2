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

float uniformRandom1D() {
    return uniformRandom();
}
Vector2 uniformRandom2D() {
    return Vector2(uniformRandom1D(), uniformRandom1D());
}

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
	BSDF * bsdf;
	Vertex vertices [3];
	
	Triangle() {}
	
	Triangle(BSDF *  bsdf, Vertex *vertices) {
		this->bsdf = bsdf;
		this->vertices[0] = vertices[0];
		this->vertices[1] = vertices[1];
		this->vertices[2] = vertices[2];
	}
	
	bool intersects(
    	const ray & Ray, intersection & Intersection) const {
        const Vector3 & v0 = vertices[0].position;
        const Vector3 & v1 = vertices[1].position;
        const Vector3 & v2 = vertices[2].position;
        
        Vector3 u = v1 - v0;
        Vector3 v = v2 - v0;
        
        Vector3 p = Ray.direction.cross(v);
        float d = u.dot(p);
        
        if (std::abs(d) < AURORA_EPSILON)
            return false;
        
        Vector3 t = Ray.origin - v0;
        float inverseD = 1.0f / d;
        
        float alpha = t.dot(p) * inverseD;
        
        if (alpha < 0.0f || alpha > 1.0f)
            return false;
            
        Vector3 q = t.cross(u);
        
        float beta = Ray.direction.dot(q) * inverseD;
        
        if (beta < 0.0f || alpha + beta > 1.0f)
            return false;
        
        float t0 = v.dot(q) * inverseD;
        
        if (t0 < AURORA_EPSILON)
            return false;
        
        Intersection.hit = true;
        Intersection.distance = t0;
        
        return true;
    }
	
	shaderGlobals calculateShaderGlobals(intersection Intersection ,ray Ray)
	{
		shaderGlobals sg;
		
		sg.point = Ray.point(Intersection.distance);
		
		Vector3 b = barycentric(sg.point, vertices[0].position, vertices[1].position, vertices[2].position);
        
        sg.normal = (vertices[0].normal * b.x + vertices[1].normal * b.y + vertices[2].normal * b.z).normalize();
        sg.uv = vertices[0].uv * b.x + vertices[1].uv * b.y + vertices[2].uv * b.z;
        
        sg.uv = Vector2(b.x, b.y);
        
        calculateTangents(sg.normal,sg.tangentU,sg.tangentV);
	
        
        sg.viewDirection = -Ray.direction;
       
		return sg;
	}
	
	virtual Vector3 uniformSample(const Vector2 & sample) const {
        const Vector3 & v0 = vertices[0].position;
        const Vector3 & v1 = vertices[1].position;
        const Vector3 & v2 = vertices[2].position;
        
        Vector3 b = uniformSampleTriangle(sample);
        
        return b.x * v0 + b.y * v1 + b.z * v2;
    }
	
	float surfaceArea()
	{
		return 0.0;
	}
		
};

struct Scene {
    std::vector<Triangle*> triangles;
    std::vector<Triangle *> lightGroup;
    
    Scene() {}
    Scene(const std::vector<Triangle *> & triangles) {
        this->triangles = triangles;
    }
    
    bool intersects(ray Ray, intersection & Intersection) const {
        for (int i = 0; i < triangles.size(); i++) {
            Triangle * triangle = triangles[i];
            
            intersection temp;
            triangle->intersects(Ray,temp);
            
            if (temp.hit && temp.distance < Intersection.distance) {
                Intersection.hit = temp.hit;
                Intersection.distance = temp.distance;
                Intersection.index = i;
            }
        }
        
        return Intersection.hit;
    }
};

struct film 
{
	float width;
	float height;
	
	film() {}
	film(float width, float height)
	{
		this->width = width;
		this->height = height;
	}
	
	float aspectRatio()
	{
		return width/height;
		
	}
};


struct camera
{
	float fieldOfView;
	film Film;
	Matrix4 worldMatrix;
	
	camera() {}
	
	camera(float fieldOfView, film Film, Matrix4 worldMatrix)
	{
		this->fieldOfView = fieldOfView;
		this->Film = Film;
		this->worldMatrix = worldMatrix;
	}
	
	void lookAt(Vector3 position, Vector3 target, Vector3 up)
	{
		Vector3 W = (position - target).normalize();
		Vector3 U = W.cross(up).normalize();
		Vector3 V = W.cross(U);
		
		worldMatrix[0][0]= U.x;
		worldMatrix[0][1]= U.y;
		worldMatrix[0][2]= U.z;
		worldMatrix[0][3]= 0;
		
		worldMatrix[1][0]= V.x;
		worldMatrix[1][1]= V.y;
		worldMatrix[1][2]= V.z;
		worldMatrix[1][3]= 0;
		
		worldMatrix[2][0]= W.x;
		worldMatrix[2][1]= W.y;
		worldMatrix[2][2]= W.z;
		worldMatrix[2][3]= 0;
		
		worldMatrix[3][0]= position.x;
		worldMatrix[3][1]= position.y;
		worldMatrix[3][2]= position.z;
		worldMatrix[3][3]= 1;
	}
	
	ray generateRay (float x,float y, Vector2 sample)
	{
		float xndc = (x + 0.5 + sample.x)/Film.width;
		float yndc = (y + 0.5 + sample.y)/Film.height;
		
		float xscreen = 2*xndc - 1;
		float yscreen = 1 - 2*yndc;
		
		float a = Film.width/Film.height;
			
		float d = tan(fieldOfView/2);
		
		float xc = a * d * xscreen;
		float yc = d * yscreen;
		float zc = -1;
		
		Vector3 vetor = Vector3(xc,yc,zc);
		
		Vector3 pLinha = vetor * worldMatrix;
		
		Vector3 p;
		p *= worldMatrix;
		
		ray R;
		
		R.direction = (pLinha - p).normalize();
		R.origin = p;
		
		return R;
		
	}
	
};

struct renderOptions
{
	int width;
	int height;
	int maximumDepth;
	int cameraSamples;
	int lightSamples;
	int diffuseSamples;
	float filterWidth;
	float gamma;
	float exposure;
	
	renderOptions() {}
	
	renderOptions(
	int width,
	int height,
	int maximumDepth,
	int cameraSamples,
	int lightSamples,
	int diffuseSamples,
	float filterWidth,
	float gamma,
	float exposure)
	{
		this->width=width;
		this->height=height;
		this->maximumDepth=maximumDepth;
		this->cameraSamples=cameraSamples;
		this->lightSamples=lightSamples;
		this->diffuseSamples=diffuseSamples;
		this->filterWidth=filterWidth;
		this->gamma=gamma;
		this->exposure=exposure;	
	}	
};

struct renderer
{
	renderOptions options;
	camera Camera;
	Scene scene;
	
	renderer() {}
	
	renderer(renderOptions options, camera Camera, Scene scene)
	{
		this->options=options;
		this->Camera=Camera;
		this->scene=scene;
	}
	
	Color3 computerDirectIllumination(BSDF bsdf, shaderGlobals shaderglobals)
	{
		if(scene.lightGroup.size() == 0)
		{
			return Color3();
		}
		else
		{
			int index = uniformRandom() * (scene.lightGroup.size() - 1);
			Triangle * light = scene.lightGroup[index];
			
			shaderglobals.lightPoint =  light->uniformSample(uniformRandom2D());
			
			Vector3 wi = shaderglobals.lightPoint - shaderglobals.point;
			float distance2 = wi.length2();
			wi.normalize();
			
			ray Ray(shaderglobals.point,wi); 
			
			intersection Intersection;
			scene.intersects(Ray,Intersection);
			shaderGlobals sglight = light.calculateShaderGlobals(Intersection,Ray);
			
		}
		
		
		return bsdf.color;
	}
	
	Color3 computerIndirectIllumination(BSDF bsdf, shaderGlobals sg, int depth)
	{
        return Color3();	
	}
	
	Color3 trace(ray Ray, int depth)
	{
		intersection Intersection;

		if (scene.intersects(Ray, Intersection)) {
            	Triangle * triangle = scene.triangles[Intersection.index];
            	BSDF * bsdf = triangle->bsdf;
            	shaderGlobals sg = triangle->calculateShaderGlobals(Intersection, Ray);
            	return computerDirectIllumination(*bsdf,sg);
		}
		else
			return Color3();
	}
	
	Image3 render()
	{
		Image3 im(options.width, options.height);
		
		for(int i=0;i<options.width;i++)
		{
			for(int j=0;j<options.height;j++)
			{
				Color3 colorOutput(0.0, 0.0, 0.0);
				
				for(int k=0;k<options.cameraSamples;k++)
				{
					Vector2 s = Vector2(uniformRandom(),uniformRandom()) - Vector2(0.5,0.5);
					ray Ray = Camera.generateRay(i,j,s);
					colorOutput += trace(Ray, 0);
				}
				
				colorOutput /= options.cameraSamples;
				
				im(i, j) = colorOutput;
			}
		}
		
		
		
		return im;
	}
	
	
	
	
};




int main(int argc, char ** argv) {
	
    Vertex v1[3];
    Vertex v2[3];
    
    renderOptions renderoptions(500, 500, 1, 4, 1, 1, 2, 2.2, 0);
	
	v1[0].position = Vector3(0.0, 0.0, 0.0);
	v1[0].normal = Vector3(0.0, 0.0, 1.0);
	v1[0].uv = Vector2(0.0, 0.0);
	
	v1[1].position = Vector3(2.0, 0.0, 0.0);
	v1[1].normal = Vector3(0.0, 0.0, 1.0);
	v1[1].uv = Vector2(1.0, 0.0);
	
	v1[2].position = Vector3(1.0, 2.0, 0.0);
	v1[2].normal = Vector3(0.0, 0.0, 1.0);
	v1[2].uv = Vector2(0.0, 1.0);
	//////
	v2[0].position = Vector3(2.0, 0.0, 10.0);
	v2[0].normal = Vector3(0.0, 0.0, 1.0);
	v2[0].uv = Vector2(0.0, 0.0);
	
	v2[1].position = Vector3(4.0, 0.0, 10.0);
	v2[1].normal = Vector3(0.0, 0.0, 1.0);
	v2[1].uv = Vector2(1.0, 0.0);
	
	v2[2].position = Vector3(3.0, 2.0, 10.0);
	v2[2].normal = Vector3(0.0, 0.0, 1.0);
	v2[2].uv = Vector2(0.0, 1.0);
	
	Color3 white(1.0, 1.0, 1.0);
	BSDF * light = new BSDF (BSDFType::Light, white);
	
	
	Matrix4 matriz;
	
	film Film = film(500,500);
	camera Camera = camera(radians(45),Film,matriz);
	
	Camera.lookAt(Vector3(1,1,35),Vector3(1,1,0),Vector3(0,1,0));			
	
	Color3 red(1.0, 0.0, 0.0);
	BSDF * diffuse = new BSDF (BSDFType::Diffuse, red);
	Triangle* t1 = new Triangle(diffuse, v1);
	Triangle* t2 = new Triangle(light, v2);
	
	vector<Triangle*> triangles = {t1,t2};

	
	Scene scene (triangles);
	scene.lightGroup.push_back(t2);
	
	renderer render(renderoptions, Camera, scene); 
	
	Image3 m = render.render();
	
	writeImage("output.ppm",&m);
	
	delete t1;
	delete t2;
	delete diffuse;
	delete light;
    
	return 0;
}
