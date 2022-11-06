// simple toon vertex shader
// www.lighthouse3d.com

//
varying vec3 normal, lightDir;
//
//void main()
//{	
//	lightDir = normalize(vec3(gl_LightSource[0].position));
//	normal = normalize(gl_NormalMatrix * gl_Normal);
//		
//	gl_Position = ftransform();
//}
//
uniform vec3 lightposition;

void main()
{	
	//lightDir = normalize(vec3(gl_LightSource[0].position));
	lightDir = normalize(lightposition);
	normal = normalize(gl_NormalMatrix * gl_Normal);
		
gl_Position = ftransform();
}