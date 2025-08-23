#version 430

in Data
{
	vec3 FrontColor;
	vec3 BackColor;
	vec2 TexCoord;
} data;
 
 
out vec4 FragColor;
 
uniform sampler2D Tex;
 
void main()
{
	if ( gl_FrontFacing )
		FragColor = vec4(data.FrontColor, 1);
	else 
		FragColor = vec4(data.BackColor, 1);
 
	FragColor *= texture(Tex, data.TexCoord);
}



Phong Shading.
Vertex Shader:
Code glsl:

#version 430
 
in vec3 VertexPosition;
in vec3 VertexNormal;
in vec2 VertexTex;
 
out Data
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} data;
 
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;
 
void main()
{
	data.Normal = normalize( NormalMatrix * VertexNormal );
	data.Position = vec3( ModelViewMatrix * vec4( VertexPosition, 1 ) );
	data.TexCoord = VertexTex;
 
	gl_Position = MVP * vec4( VertexPosition, 1 );
}


Fragment Shader:
Code glsl:

#version 430
 
struct LightInfo
{
	vec3 Position;	//Light Position in eye-coords
	vec3 La;		//Ambient light intensity
	vec3 Ld;		//Diffuse light intensity
	vec3 Ls;		//Specular light intensity
};
 
struct MaterialInfo
{
	vec3 Ka;			//Ambient reflectivity
	vec3 Kd;			//Diffuse reflectivity
	vec3 Ks;			//Specular reflectivity
	float Shininess;	//Specular shininess factor
};
 
in Data
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoord;
} data;
 
out vec4 FragColor;
 
uniform LightInfo Light[LIGHTCOUNT];
uniform MaterialInfo Material;
uniform sampler2D Tex;
 
void light( int lightIndex, vec3 position, vec3 norm, out vec3 ambient, out vec3 diffuse, out vec3 spec )
{
	vec3 n = normalize( norm );
	vec3 s = normalize( Light[lightIndex].Position - position );
	vec3 v = normalize( -position );
	vec3 r = reflect( -s, n );
 
	ambient = Light[lightIndex].La * Material.Ka;
 
	float sDotN = max( dot( s, n ), 0.0 );
	diffuse = Light[lightIndex].Ld * Material.Kd * sDotN;
 
 
	spec = Light[lightIndex].Ls * Material.Ks * pow( max( dot(r,v) , 0.0 ), Material.Shininess ); 
}
 
void main()
{
 
	vec3 ambientSum = vec3(0);
	vec3 diffuseSum = vec3(0);
	vec3 specSum = vec3(0);
	vec3 ambient, diffuse, spec;
 
	if ( gl_FrontFacing )
	{
		for( int i=0; i<LIGHTCOUNT; ++i )
		{
			light( i, data.Position, data.Normal, ambient, diffuse, spec );
			ambientSum += ambient;
			diffuseSum += diffuse;
			specSum += spec;
		}
	}
	else
	{
		for( int i=0; i<LIGHTCOUNT; ++i )
		{
			light( i, data.Position, -data.Normal, ambient, diffuse, spec );
			ambientSum += ambient;
			diffuseSum += diffuse;
			specSum += spec;
		}
	}
	ambientSum /= LIGHTCOUNT;
 
	vec4 texColor = texture(Tex, data.TexCoord);
 
	FragColor = vec4( ambientSum + diffuseSum, 1 ) * texColor + vec4( specSum, 1 );
}

Last edited by Betrayal; 03-21-2015 at 02:39 AM. 

