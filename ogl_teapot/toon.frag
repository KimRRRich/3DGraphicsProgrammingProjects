// simple toon fragment shader
// www.lighthouse3d.com

varying vec3 normal, lightDir;
uniform vec4 color1,color2,color3,color4;

void main()
{
	float intensity;
	vec3 n;
	vec4 color;

	n = normalize(normal);
	intensity = max(dot(lightDir,n),0.0); 

	if (intensity > 0.98)
		//color = vec4(0.8,0.8,0.8,1.0);
		color =color1;
	else if (intensity > 0.5)
		//color = vec4(0.5,0.5,0.4,1.0);
		color =color2;
	else if (intensity > 0.25)
		//color = vec4(0.25,0.25,0.2,1.0);
		color =color3;
	else
		//color = vec4(0.1,0.1,0.1,1.0);
		color =color4;
		
	gl_FragColor = color;
}


