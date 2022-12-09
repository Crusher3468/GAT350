#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 
//scanline
//const float screen_height = 600.0; 

//Wave
//uniform float offset;
  
uniform sampler2D textureMap; 
  
void main() 
{ 
 fcolor = texture(textureMap, texcoord); 

 /*
 // black / white 
  vec3 color = texture(textureMap, texcoord).rgb; 
 float avg = (color.r + color.g + color.b) / 3.0; 
 fcolor = vec4(vec3(avg), 1); 

 // invert 
 vec3 color = texture(textureMap, texcoord).rgb; 
 fcolor = vec4(1.0 - color, 1); 

 //scanline
 vec3 color = texture(textureMap, texcoord).rgb; 
 // get the screen y position (uv coordinates range 0 <-> 1) 
 int y = int(texcoord.y * screen_height); 
 // set the alpha based on the modulus of the y position 
 float alpha = (y % 5 != 0) ? 1 : 0; 
 fcolor = vec4(color *alpha, 1); 

 // wave 
 vec2 ttexcoord = texcoord; 
 ttexcoord.x += sin(ttexcoord.y * 30.0 + offset) / 100.0; 
 fcolor = texture(textureMap, ttexcoord); 
 */
} 
