//setup for 2 texture
varying vec2 texcoord0;
varying vec2 texcoord1;

uniform sampler2DRect tex0;
uniform vec3 which;

void main(){
    vec4 color = texture2DRect(tex0, texcoord0);
//    color -= 0.01;
    
    gl_FragColor = vec4(color.rgb * which, 1.0);
    
}
