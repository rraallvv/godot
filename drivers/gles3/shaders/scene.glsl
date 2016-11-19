[vertex]


/*
from VisualServer:

ARRAY_VERTEX=0,
ARRAY_NORMAL=1,
ARRAY_TANGENT=2,
ARRAY_COLOR=3,
ARRAY_TEX_UV=4,
ARRAY_TEX_UV2=5,
ARRAY_BONES=6,
ARRAY_WEIGHTS=7,
ARRAY_INDEX=8,
*/

//hack to use uv if no uv present so it works with lightmap


/* INPUT ATTRIBS */

layout(location=0) in highp vec4 vertex_attrib;
layout(location=1) in vec3 normal_attrib;
layout(location=2) in vec4 tangent_attrib;
layout(location=3) in vec4 color_attrib;
layout(location=4) in vec2 uv_attrib;
layout(location=5) in vec2 uv2_attrib;

uniform float normal_mult;

#ifdef USE_SKELETON
layout(location=6) mediump ivec4 bone_indices; // attrib:6
layout(location=7) mediump vec4 bone_weights; // attrib:7
uniform highp sampler2D skeleton_matrices;
#endif

#ifdef USE_ATTRIBUTE_INSTANCING

layout(location=8) in highp vec4 instance_xform0;
layout(location=9) in highp vec4 instance_xform1;
layout(location=10) in highp vec4 instance_xform2;
layout(location=11) in lowp vec4 instance_color;

#endif

layout(std140) uniform SceneData { //ubo:0

	highp mat4 projection_matrix;
	highp mat4 camera_inverse_matrix;
	highp mat4 camera_matrix;
	highp vec4 time;

	highp vec4 ambient_light_color;
	highp vec4 bg_color;
	float ambient_energy;
	float bg_energy;

	float shadow_z_offset;
	float shadow_z_slope_scale;
	float shadow_dual_paraboloid_render_zfar;
	float shadow_dual_paraboloid_render_side;

	vec2 shadow_atlas_pixel_size;
	vec2 directional_shadow_pixel_size;

	float reflection_multiplier;

};

uniform highp mat4 world_transform;

#ifdef USE_LIGHT_DIRECTIONAL

layout(std140) uniform DirectionalLightData { //ubo:3

	highp vec4 light_pos_inv_radius;
	mediump vec4 light_direction_attenuation;
	mediump vec4 light_color_energy;
	mediump vec4 light_params; //cone attenuation, angle, specular, shadow enabled,
	mediump vec4 light_clamp;
	mediump vec4 shadow_color;
	highp mat4 shadow_matrix1;
	highp mat4 shadow_matrix2;
	highp mat4 shadow_matrix3;
	highp mat4 shadow_matrix4;
	mediump vec4 shadow_split_offsets;
};

#endif


/* Varyings */

out highp vec3 vertex_interp;
out vec3 normal_interp;

#if defined(ENABLE_COLOR_INTERP)
out vec4 color_interp;
#endif

#if defined(ENABLE_UV_INTERP)
out vec2 uv_interp;
#endif

#if defined(ENABLE_UV2_INTERP)
out vec2 uv2_interp;
#endif


#if defined(ENABLE_TANGENT_INTERP)
out vec3 tangent_interp;
out vec3 binormal_interp;
#endif


#if !defined(USE_DEPTH_SHADOWS) && defined(USE_SHADOW_PASS)

varying vec4 position_interp;

#endif


VERTEX_SHADER_GLOBALS


#if defined(USE_MATERIAL)

layout(std140) uniform UniformData { //ubo:1

MATERIAL_UNIFORMS

};

#endif

#ifdef RENDER_SHADOW_DUAL_PARABOLOID

out highp float dp_clip;

#endif

void main() {

	highp vec4 vertex = vertex_attrib; // vec4(vertex_attrib.xyz * data_attrib.x,1.0);
	highp mat4 modelview = camera_inverse_matrix * world_transform;
	vec3 normal = normal_attrib * normal_mult;

#if defined(ENABLE_TANGENT_INTERP)
	vec3 tangent = tangent_attrib.xyz;
	tangent*=normal_mult;
	float binormalf = tangent_attrib.a;
#endif

#ifdef USE_SKELETON

	{
		//skeleton transform
		highp mat4 m=mat4(texture2D(skeleton_matrices,vec2((bone_indices.x*3.0+0.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.x*3.0+1.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.x*3.0+2.0)*skeltex_pixel_size,0.0)),vec4(0.0,0.0,0.0,1.0))*bone_weights.x;
		m+=mat4(texture2D(skeleton_matrices,vec2((bone_indices.y*3.0+0.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.y*3.0+1.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.y*3.0+2.0)*skeltex_pixel_size,0.0)),vec4(0.0,0.0,0.0,1.0))*bone_weights.y;
		m+=mat4(texture2D(skeleton_matrices,vec2((bone_indices.z*3.0+0.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.z*3.0+1.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.z*3.0+2.0)*skeltex_pixel_size,0.0)),vec4(0.0,0.0,0.0,1.0))*bone_weights.z;
		m+=mat4(texture2D(skeleton_matrices,vec2((bone_indices.w*3.0+0.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.w*3.0+1.0)*skeltex_pixel_size,0.0)),texture2D(skeleton_matrices,vec2((bone_indices.w*3.0+2.0)*skeltex_pixel_size,0.0)),vec4(0.0,0.0,0.0,1.0))*bone_weights.w;

		vertex = vertex_in * m;
		normal = (vec4(normal,0.0) * m).xyz;
#if defined(ENABLE_TANGENT_INTERP)
		tangent = (vec4(tangent,0.0) * m).xyz;
#endif
	}

#endif

#if !defined(SKIP_TRANSFORM_USED)

	vertex = modelview * vertex;
	normal = normalize((modelview * vec4(normal,0.0)).xyz);
#endif

#if defined(ENABLE_TANGENT_INTERP)
# if !defined(SKIP_TRANSFORM_USED)

	tangent=normalize((modelview * vec4(tangent,0.0)).xyz);
# endif
	vec3 binormal = normalize( cross(normal,tangent) * binormalf );
#endif



#if defined(ENABLE_COLOR_INTERP)
	color_interp = color_attrib;
#endif

#if defined(ENABLE_UV_INTERP)
	uv_interp = uv_attrib;
#endif

#if defined(ENABLE_UV2_INTERP)
	uv2_interp = uv2_attrib;
#endif

{

VERTEX_SHADER_CODE

}

	vertex_interp = vertex.xyz;
	normal_interp = normal;

#if defined(ENABLE_TANGENT_INTERP)
	tangent_interp = tangent;
	binormal_interp = binormal;
#endif

#ifdef RENDER_SHADOW


#ifdef RENDER_SHADOW_DUAL_PARABOLOID

	vertex_interp.z*= shadow_dual_paraboloid_render_side;
	normal_interp.z*= shadow_dual_paraboloid_render_side;

	dp_clip=vertex_interp.z; //this attempts to avoid noise caused by objects sent to the other parabolloid side due to bias

	//for dual paraboloid shadow mapping, this is the fastest but least correct way, as it curves straight edges

	highp vec3 vtx = vertex_interp+normalize(vertex_interp)*shadow_z_offset;
	highp float distance = length(vtx);
	vtx = normalize(vtx);
	vtx.xy/=1.0-vtx.z;
	vtx.z=(distance/shadow_dual_paraboloid_render_zfar);
	vtx.z=vtx.z * 2.0 - 1.0;

	vertex.xyz=vtx;
	vertex.w=1.0;


#else

	float z_ofs = shadow_z_offset;
	z_ofs += (1.0-abs(normal_interp.z))*shadow_z_slope_scale;
	vertex_interp.z-=z_ofs;

#endif //RENDER_SHADOW_DUAL_PARABOLOID

#endif //RENDER_SHADOW


#if !defined(SKIP_TRANSFORM_USED) && !defined(RENDER_SHADOW_DUAL_PARABOLOID)
	gl_Position = projection_matrix * vec4(vertex_interp,1.0);
#else
	gl_Position = vertex;
#endif


}


[fragment]



#define M_PI 3.14159265359

/* Varyings */

#if defined(ENABLE_COLOR_INTERP)
in vec4 color_interp;
#endif

#if defined(ENABLE_UV_INTERP)
in vec2 uv_interp;
#endif

#if defined(ENABLE_UV2_INTERP)
in vec2 uv2_interp;
#endif

#if defined(ENABLE_TANGENT_INTERP)
in vec3 tangent_interp;
in vec3 binormal_interp;
#endif

in highp vec3 vertex_interp;
in vec3 normal_interp;


/* PBR CHANNELS */

//used on forward mainly
uniform bool no_ambient_light;

uniform sampler2D brdf_texture; //texunit:-1

#ifdef USE_RADIANCE_MAP

uniform sampler2D radiance_map; //texunit:-2


layout(std140) uniform Radiance { //ubo:2

	mat4 radiance_inverse_xform;
	vec3 radiance_box_min;
	vec3 radiance_box_max;
	float radiance_ambient_contribution;

};

#endif

/* Material Uniforms */


FRAGMENT_SHADER_GLOBALS


#if defined(USE_MATERIAL)

layout(std140) uniform UniformData {

MATERIAL_UNIFORMS

};

#endif


layout(std140) uniform SceneData {

	highp mat4 projection_matrix;
	highp mat4 camera_inverse_matrix;
	highp mat4 camera_matrix;
	highp vec4 time;

	highp vec4 ambient_light_color;
	highp vec4 bg_color;
	float ambient_energy;
	float bg_energy;

	float shadow_z_offset;
	float shadow_z_slope_scale;
	float shadow_dual_paraboloid_render_zfar;
	float shadow_dual_paraboloid_render_side;

	vec2 shadow_atlas_pixel_size;
	vec2 directional_shadow_pixel_size;

	float reflection_multiplier;

};

//directional light data

#ifdef USE_LIGHT_DIRECTIONAL

layout(std140) uniform DirectionalLightData {

	highp vec4 light_pos_inv_radius;
	mediump vec4 light_direction_attenuation;
	mediump vec4 light_color_energy;
	mediump vec4 light_params; //cone attenuation, angle, specular, shadow enabled,
	mediump vec4 light_clamp;
	mediump vec4 shadow_color;
	highp mat4 shadow_matrix1;
	highp mat4 shadow_matrix2;
	highp mat4 shadow_matrix3;
	highp mat4 shadow_matrix4;
	mediump vec4 shadow_split_offsets;
};


uniform highp sampler2DShadow directional_shadow; //texunit:-4

#endif

//omni and spot

struct LightData {

	highp vec4 light_pos_inv_radius;
	mediump vec4 light_direction_attenuation;
	mediump vec4 light_color_energy;
	mediump vec4 light_params; //cone attenuation, angle, specular, shadow enabled,
	mediump vec4 light_clamp;
	mediump vec4 shadow_color;
	highp mat4 shadow_matrix;

};


layout(std140) uniform OmniLightData { //ubo:4

	LightData omni_lights[MAX_LIGHT_DATA_STRUCTS];
};

layout(std140) uniform SpotLightData { //ubo:5

	LightData spot_lights[MAX_LIGHT_DATA_STRUCTS];
};


uniform highp sampler2DShadow shadow_atlas; //texunit:-3


struct ReflectionData {

	mediump vec4 box_extents;
	mediump vec4 box_offset;
	mediump vec4 params; // intensity, 0, interior , boxproject
	mediump vec4 ambient; //ambient color, energy
	mediump vec4 atlas_clamp;
	highp mat4 local_matrix; //up to here for spot and omni, rest is for directional
	//notes: for ambientblend, use distance to edge to blend between already existing global environment
};

layout(std140) uniform ReflectionProbeData { //ubo:6

	ReflectionData reflections[MAX_REFLECTION_DATA_STRUCTS];
};
uniform mediump sampler2D reflection_atlas; //texunit:-5


#ifdef USE_FORWARD_LIGHTING

uniform int omni_light_indices[MAX_FORWARD_LIGHTS];
uniform int omni_light_count;

uniform int spot_light_indices[MAX_FORWARD_LIGHTS];
uniform int spot_light_count;

uniform int reflection_indices[MAX_FORWARD_LIGHTS];
uniform int reflection_count;

#endif



#ifdef USE_MULTIPLE_RENDER_TARGETS

layout(location=0) out vec4 diffuse_buffer;
layout(location=1) out vec4 specular_buffer;
layout(location=2) out vec4 normal_mr_buffer;

#else

layout(location=0) out vec4 frag_color;

#endif


// GGX Specular
// Source: http://www.filmicworlds.com/images/ggx-opt/optimized-ggx.hlsl
float G1V(float dotNV, float k)
{
    return 1.0 / (dotNV * (1.0 - k) + k);
}

float specularGGX(vec3 N, vec3 V, vec3 L, float roughness, float F0)
{
    float alpha = roughness * roughness;

    vec3 H = normalize(V + L);

    float dotNL = max(dot(N,L), 0.0 );
    float dotNV = max(dot(N,V), 0.0 );
    float dotNH = max(dot(N,H), 0.0 );
    float dotLH = max(dot(L,H), 0.0 );

    // D
    float alphaSqr = alpha * alpha;
    float pi = M_PI;
    float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0;
    float D = alphaSqr / (pi * denom * denom);

    // F
    float dotLH5 = pow(1.0 - dotLH, 5.0);
    float F = F0 + (1.0 - F0) * (dotLH5);

    // V
    float k = alpha / 2.0f;
    float vis = G1V(dotNL, k) * G1V(dotNV, k);

    return dotNL * D * F * vis;
}

void light_compute(vec3 normal, vec3 light_vec,vec3 eye_vec,vec3 light_color,vec3 diffuse_color, vec3 specular_color, float roughness, inout vec3 diffuse, inout vec3 specular) {

	diffuse += max(0.0,dot(normal,light_vec)) * light_color * diffuse_color;
	//specular += specular_ggx( roughness, max(0.0,dot(normal,eye_vec)) ) * specular_color * attenuation;
	float s = roughness > 0.0 ? specularGGX(normal,eye_vec,light_vec,roughness,1.0) : 0.0;
	specular += s * light_color * specular_color;
}


float sample_shadow(highp sampler2DShadow shadow, vec2 shadow_pixel_size, vec2 pos, float depth, vec4 clamp_rect) {

#ifdef SHADOW_MODE_PCF_13

	float avg=textureProj(shadow,vec4(pos,depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(shadow_pixel_size.x,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(-shadow_pixel_size.x,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,-shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(shadow_pixel_size.x,shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(-shadow_pixel_size.x,shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(shadow_pixel_size.x,-shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(-shadow_pixel_size.x,-shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(shadow_pixel_size.x*2.0,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(-shadow_pixel_size.x*2.0,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,shadow_pixel_size.y*2.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,-shadow_pixel_size.y*2.0),depth,1.0));
	return avg*(1.0/13.0);

#endif

#ifdef SHADOW_MODE_PCF_5

	float avg=textureProj(shadow,vec4(pos,depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(shadow_pixel_size.x,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(-shadow_pixel_size.x,0.0),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,shadow_pixel_size.y),depth,1.0));
	avg+=textureProj(shadow,vec4(pos+vec2(0.0,-shadow_pixel_size.y),depth,1.0));
	return avg*(1.0/5.0);
#endif

#if !defined(SHADOW_MODE_PCF_5) && !defined(SHADOW_MODE_PCF_13)

	return textureProj(shadow,vec4(pos,depth,1.0));
#endif

}

#ifdef RENDER_SHADOW_DUAL_PARABOLOID

in highp float dp_clip;

#endif

void light_process_omni(int idx, vec3 vertex, vec3 eye_vec,vec3 normal,vec3 albedo, vec3 specular, float roughness, inout vec3 diffuse_light, inout vec3 specular_light) {

	vec3 light_rel_vec = omni_lights[idx].light_pos_inv_radius.xyz-vertex;
	float normalized_distance = length( light_rel_vec )*omni_lights[idx].light_pos_inv_radius.w;
	vec3 light_attenuation = vec3(pow( max(1.0 - normalized_distance, 0.0), omni_lights[idx].light_direction_attenuation.w ));

	if (omni_lights[idx].light_params.w>0.5) {
		//there is a shadowmap

		highp vec3 splane=(omni_lights[idx].shadow_matrix * vec4(vertex,1.0)).xyz;
		float shadow_len=length(splane);
		splane=normalize(splane);
		vec4 clamp_rect=omni_lights[idx].light_clamp;

		if (splane.z>=0.0) {

			splane.z+=1.0;

			clamp_rect.y+=clamp_rect.w;

		} else {

			splane.z=1.0 - splane.z;

			//if (clamp_rect.z<clamp_rect.w) {
			//	clamp_rect.x+=clamp_rect.z;
			//} else {
			//	clamp_rect.y+=clamp_rect.w;
			//}

		}

		splane.xy/=splane.z;
		splane.xy=splane.xy * 0.5 + 0.5;
		splane.z = shadow_len * omni_lights[idx].light_pos_inv_radius.w;

		splane.xy = clamp_rect.xy+splane.xy*clamp_rect.zw;

		light_attenuation*=mix(omni_lights[idx].shadow_color.rgb,vec3(1.0),sample_shadow(shadow_atlas,shadow_atlas_pixel_size,splane.xy,splane.z,clamp_rect));
	}

	light_compute(normal,normalize(light_rel_vec),eye_vec,omni_lights[idx].light_color_energy.rgb*light_attenuation,albedo,specular,roughness,diffuse_light,specular_light);

}

void light_process_spot(int idx, vec3 vertex, vec3 eye_vec, vec3 normal, vec3 albedo, vec3 specular, float roughness, inout vec3 diffuse_light, inout vec3 specular_light) {

	vec3 light_rel_vec = spot_lights[idx].light_pos_inv_radius.xyz-vertex;
	float normalized_distance = length( light_rel_vec )*spot_lights[idx].light_pos_inv_radius.w;
	vec3 light_attenuation = vec3(pow( max(1.0 - normalized_distance, 0.0), spot_lights[idx].light_direction_attenuation.w ));
	vec3 spot_dir = spot_lights[idx].light_direction_attenuation.xyz;
	float spot_cutoff=spot_lights[idx].light_params.y;
	float scos = max(dot(-normalize(light_rel_vec), spot_dir),spot_cutoff);
	float rim = (1.0 - scos) / (1.0 - spot_cutoff);
	light_attenuation *= 1.0 - pow( rim, spot_lights[idx].light_params.x);

	if (spot_lights[idx].light_params.w>0.5) {
		//there is a shadowmap
		highp vec4 splane=(spot_lights[idx].shadow_matrix * vec4(vertex,1.0));
		splane.xyz/=splane.w;
		light_attenuation*=mix(spot_lights[idx].shadow_color.rgb,vec3(1.0),sample_shadow(shadow_atlas,shadow_atlas_pixel_size,splane.xy,splane.z,spot_lights[idx].light_clamp));
	}

	light_compute(normal,normalize(light_rel_vec),eye_vec,spot_lights[idx].light_color_energy.rgb*light_attenuation,albedo,specular,roughness,diffuse_light,specular_light);

}

void reflection_process(int idx, vec3 vertex, vec3 normal,float roughness,vec3 ambient,vec3 skybox,vec2 brdf, inout highp vec4 reflection_accum,inout highp vec4 ambient_accum) {

	vec3 ref_vec = normalize(reflect(vertex,normal));
	vec3 local_pos = (reflections[idx].local_matrix * vec4(vertex,1.0)).xyz;
	vec3 box_extents = reflections[idx].box_extents.xyz;

	if (any(greaterThan(abs(local_pos),box_extents))) { //out of the reflection box
		return;
	}

	vec3 inner_pos = abs(local_pos / box_extents);
	float blend = max(inner_pos.x,max(inner_pos.y,inner_pos.z));
	//make blend more rounded
	blend=mix(length(inner_pos),blend,blend);
	blend*=blend;
	blend=1.001-blend;

	if (reflections[idx].params.x>0.0){// compute reflection

		vec3 local_ref_vec = (reflections[idx].local_matrix * vec4(ref_vec,0.0)).xyz;

		if (reflections[idx].params.w > 0.5) { //box project

			vec3 nrdir = normalize(local_ref_vec);
			vec3 rbmax = (box_extents - local_pos)/nrdir;
			vec3 rbmin = (-box_extents - local_pos)/nrdir;


			vec3 rbminmax = mix(rbmin,rbmax,greaterThan(nrdir,vec3(0.0,0.0,0.0)));

			float fa = min(min(rbminmax.x, rbminmax.y), rbminmax.z);
			vec3 posonbox = local_pos + nrdir * fa;
			local_ref_vec = posonbox - reflections[idx].box_offset.xyz;
		}



		vec3 splane=normalize(local_ref_vec);
		vec4 clamp_rect=reflections[idx].atlas_clamp;

		splane.z*=-1.0;
		if (splane.z>=0.0) {
			splane.z+=1.0;
			clamp_rect.y+=clamp_rect.w;
		} else {
			splane.z=1.0 - splane.z;
			splane.y=-splane.y;
		}

		splane.xy/=splane.z;
		splane.xy=splane.xy * 0.5 + 0.5;

		splane.xy = splane.xy * clamp_rect.zw + clamp_rect.xy;
		splane.xy = clamp(splane.xy,clamp_rect.xy,clamp_rect.xy+clamp_rect.zw);

		highp vec4 reflection;
		reflection.rgb = textureLod(reflection_atlas,splane.xy,roughness*5.0).rgb * ( brdf.x + brdf.y);
		if (reflections[idx].params.z < 0.5) {
			reflection.rgb = mix(skybox,reflection.rgb,blend);
		}
		reflection.rgb*=reflections[idx].params.x;
		reflection.a = blend;
		reflection.rgb*=reflection.a;

		reflection_accum+=reflection;
	}

	if (reflections[idx].ambient.a>0.0) { //compute ambient using skybox


		vec3 local_amb_vec = (reflections[idx].local_matrix * vec4(normal,0.0)).xyz;

		vec3 splane=normalize(local_amb_vec);
		vec4 clamp_rect=reflections[idx].atlas_clamp;

		splane.z*=-1.0;
		if (splane.z>=0.0) {
			splane.z+=1.0;
			clamp_rect.y+=clamp_rect.w;
		} else {
			splane.z=1.0 - splane.z;
			splane.y=-splane.y;
		}

		splane.xy/=splane.z;
		splane.xy=splane.xy * 0.5 + 0.5;

		splane.xy = splane.xy * clamp_rect.zw + clamp_rect.xy;
		splane.xy = clamp(splane.xy,clamp_rect.xy,clamp_rect.xy+clamp_rect.zw);

		highp vec4 ambient_out;
		ambient_out.a=blend;
		ambient_out.rgb = textureLod(reflection_atlas,splane.xy,5.0).rgb;
		ambient_out.rgb=mix(reflections[idx].ambient.rgb,ambient_out.rgb,reflections[idx].ambient.a);
		if (reflections[idx].params.z < 0.5) {
			ambient_out.rgb = mix(ambient,ambient_out.rgb,blend);
		}

		ambient_out.rgb *= ambient_out.a;
		ambient_accum+=ambient_out;
	} else {

		highp vec4 ambient_out;
		ambient_out.a=blend;
		ambient_out.rgb=reflections[idx].ambient.rgb;
		if (reflections[idx].params.z < 0.5) {
			ambient_out.rgb = mix(ambient,ambient_out.rgb,blend);
		}
		ambient_out.rgb *= ambient_out.a;
		ambient_accum+=ambient_out;

	}
}

void main() {

#ifdef RENDER_SHADOW_DUAL_PARABOLOID

	if (dp_clip>0.0)
		discard;
#endif

	//lay out everything, whathever is unused is optimized away anyway
	highp vec3 vertex = vertex_interp;
	vec3 albedo = vec3(0.8,0.8,0.8);
	vec3 specular = vec3(0.2,0.2,0.2);
	float roughness = 1.0;
	float alpha = 1.0;

#ifdef METERIAL_DOUBLESIDED
	float side=float(gl_FrontFacing)*2.0-1.0;
#else
	float side=1.0;
#endif


#if defined(ENABLE_TANGENT_INTERP)
	vec3 binormal = normalize(binormal_interp)*side;
	vec3 tangent = normalize(tangent_interp)*side;
#endif
	vec3 normal = normalize(normal_interp)*side;

#if defined(ENABLE_UV_INTERP)
	vec2 uv = uv_interp;
#endif

#if defined(ENABLE_UV2_INTERP)
	vec2 uv2 = uv2_interp;
#endif

#if defined(ENABLE_COLOR_INTERP)
	vec4 color = color_interp;
#endif

#if defined(ENABLE_NORMALMAP)

	vec3 normalmap = vec3(0.0);
#endif

	float normaldepth=1.0;



#if defined(ENABLE_DISCARD)
	bool discard_=false;
#endif

{


FRAGMENT_SHADER_CODE

}

#if defined(ENABLE_NORMALMAP)

	normal = normalize( mix(normal_interp,tangent_interp * normalmap.x + binormal_interp * normalmap.y + normal_interp * normalmap.z,normaldepth) ) * side;

#endif

#if defined(ENABLE_DISCARD)
	if (discard_) {
	//easy to eliminate dead code
		discard;
	}
#endif

#ifdef ENABLE_CLIP_ALPHA
	if (diffuse.a<0.99) {
		//used for doublepass and shadowmapping
		discard;
	}
#endif

/////////////////////// LIGHTING //////////////////////////////

	vec3 specular_light = vec3(0.0,0.0,0.0);
	vec3 ambient_light;
	vec3 diffuse_light = vec3(0.0,0.0,0.0);

	vec3 eye_vec = -normalize( vertex_interp );

#ifndef RENDER_SHADOW
	float ndotv = clamp(dot(normal,eye_vec),0.0,1.0);
	vec2 brdf = texture(brdf_texture, vec2(roughness, ndotv)).xy;
#endif

#ifdef USE_RADIANCE_MAP

	if (no_ambient_light) {
		ambient_light=vec3(0.0,0.0,0.0);
	} else {
		{



			float lod = roughness * 5.0;

			{ //read radiance from dual paraboloid

				vec3 ref_vec = reflect(-eye_vec,normal); //2.0 * ndotv * normal - view; // reflect(v, n);
				ref_vec=normalize((radiance_inverse_xform * vec4(ref_vec,0.0)).xyz);

				vec3 norm = normalize(ref_vec);
				float y_ofs=0.0;
				if (norm.z>=0.0) {

					norm.z+=1.0;
					y_ofs+=0.5;
				} else {
					norm.z=1.0 - norm.z;
					norm.y=-norm.y;
				}

				norm.xy/=norm.z;
				norm.xy=norm.xy * vec2(0.5,0.25) + vec2(0.5,0.25+y_ofs);
				vec3 radiance = textureLod(radiance_map, norm.xy, lod).xyz * ( brdf.x + brdf.y);
				specular_light=mix(albedo,radiance,specular);

			}
			//no longer a cubemap
			//vec3 radiance = textureLod(radiance_cube, r, lod).xyz * ( brdf.x + brdf.y);

		}

		{

			/*vec3 ambient_dir=normalize((radiance_inverse_xform * vec4(normal,0.0)).xyz);
			vec3 env_ambient=textureLod(radiance_cube, ambient_dir, 5.0).xyz;

			ambient_light=mix(ambient_light_color.rgb,env_ambient,radiance_ambient_contribution);*/
			ambient_light=vec3(0.0,0.0,0.0);
		}
	}

#else

	if (no_ambient_light){
		ambient_light=vec3(0.0,0.0,0.0);
	} else {
		ambient_light=ambient_light_color.rgb;
	}
#endif


#ifdef USE_LIGHT_DIRECTIONAL

	vec3 light_attenuation=vec3(1.0);

#ifdef LIGHT_DIRECTIONAL_SHADOW

	if (gl_FragCoord.w > shadow_split_offsets.w) {

	vec3 pssm_coord;

#ifdef LIGHT_USE_PSSM_BLEND
	float pssm_blend;
	vec3 pssm_coord2;
	bool use_blend=true;
	vec3 light_pssm_split_inv = 1.0/shadow_split_offsets.xyz;
	float w_inv = 1.0/gl_FragCoord.w;
#endif


#ifdef LIGHT_USE_PSSM4


	if (gl_FragCoord.w > shadow_split_offsets.y) {

		if (gl_FragCoord.w > shadow_split_offsets.x) {

			highp vec4 splane=(shadow_matrix1 * vec4(vertex,1.0));
			pssm_coord=splane.xyz/splane.w;


#if defined(LIGHT_USE_PSSM_BLEND)

			splane=(shadow_matrix2 * vec4(vertex,1.0));
			pssm_coord2=splane.xyz/splane.w;
			pssm_blend=smoothstep(0.0,light_pssm_split_inv.x,w_inv);
#endif

		} else {

			highp vec4 splane=(shadow_matrix2 * vec4(vertex,1.0));
			pssm_coord=splane.xyz/splane.w;

#if defined(LIGHT_USE_PSSM_BLEND)
			splane=(shadow_matrix3 * vec4(vertex,1.0));
			pssm_coord2=splane.xyz/splane.w;
			pssm_blend=smoothstep(light_pssm_split_inv.x,light_pssm_split_inv.y,w_inv);
#endif

		}
	} else {


		if (gl_FragCoord.w > shadow_split_offsets.z) {

			highp vec4 splane=(shadow_matrix3 * vec4(vertex,1.0));
			pssm_coord=splane.xyz/splane.w;

#if defined(LIGHT_USE_PSSM_BLEND)
			splane=(shadow_matrix4 * vec4(vertex,1.0));
			pssm_coord2=splane.xyz/splane.w;
			pssm_blend=smoothstep(light_pssm_split_inv.y,light_pssm_split_inv.z,w_inv);
#endif

		} else {
			highp vec4 splane=(shadow_matrix4 * vec4(vertex,1.0));
			pssm_coord=splane.xyz/splane.w;
			diffuse_light*=vec3(1.0,0.4,1.0);

#if defined(LIGHT_USE_PSSM_BLEND)
			use_blend=false;

#endif

		}
	}

#endif //LIGHT_USE_PSSM4

#ifdef LIGHT_USE_PSSM2

	if (gl_FragCoord.w > shadow_split_offsets.x) {

		highp vec4 splane=(shadow_matrix1 * vec4(vertex,1.0));
		pssm_coord=splane.xyz/splane.w;


#if defined(LIGHT_USE_PSSM_BLEND)

		splane=(shadow_matrix2 * vec4(vertex,1.0));
		pssm_coord2=splane.xyz/splane.w;
		pssm_blend=smoothstep(0.0,light_pssm_split_inv.x,w_inv);
#endif

	} else {
		highp vec4 splane=(shadow_matrix2 * vec4(vertex,1.0));
		pssm_coord=splane.xyz/splane.w;
#if defined(LIGHT_USE_PSSM_BLEND)
		use_blend=false;

#endif

	}

#endif //LIGHT_USE_PSSM2

#if !defined(LIGHT_USE_PSSM4) && !defined(LIGHT_USE_PSSM2)
	{ //regular orthogonal
		highp vec4 splane=(shadow_matrix1 * vec4(vertex,1.0));
		pssm_coord=splane.xyz/splane.w;
	}
#endif


	//one one sample
	light_attenuation=mix(shadow_color.rgb,vec3(1.0),sample_shadow(directional_shadow,directional_shadow_pixel_size,pssm_coord.xy,pssm_coord.z,light_clamp));


#if defined(LIGHT_USE_PSSM_BLEND)
	if (use_blend) {
		vec3 light_attenuation2=mix(shadow_color.rgb,vec3(1.0),sample_shadow(directional_shadow,directional_shadow_pixel_size,pssm_coord2.xy,pssm_coord2.z,light_clamp));
		light_attenuation=mix(light_attenuation,light_attenuation2,pssm_blend);
	}
#endif

	}

#endif //LIGHT_DIRECTIONAL_SHADOW

	light_compute(normal,-light_direction_attenuation.xyz,eye_vec,light_color_energy.rgb*light_attenuation,albedo,specular,roughness,diffuse_light,specular_light);


#endif //#USE_LIGHT_DIRECTIONAL


#ifdef USE_FORWARD_LIGHTING

	highp vec4 reflection_accum = vec4(0.0,0.0,0.0,0.0);
	highp vec4 ambient_accum = vec4(0.0,0.0,0.0,0.0);

	for(int i=0;i<reflection_count;i++) {
		reflection_process(reflection_indices[i],vertex,normal,roughness,ambient_light,specular_light,brdf,reflection_accum,ambient_accum);
	}

	if (reflection_accum.a>0.0) {
		specular_light=reflection_accum.rgb/reflection_accum.a;
		specular_light*=specular;
	}
	if (ambient_accum.a>0.0) {
		ambient_light=ambient_accum.rgb/ambient_accum.a;
	}

	for(int i=0;i<omni_light_count;i++) {
		light_process_omni(omni_light_indices[i],vertex,eye_vec,normal,albedo,specular,roughness,diffuse_light,specular_light);
	}

	for(int i=0;i<spot_light_count;i++) {
		light_process_spot(spot_light_indices[i],vertex,eye_vec,normal,albedo,specular,roughness,diffuse_light,specular_light);
	}



#endif




#if defined(USE_LIGHT_SHADER_CODE)
//light is written by the light shader
{

LIGHT_SHADER_CODE

}
#endif

#ifdef RENDER_SHADOW
//nothing happens, so a tree-ssa optimizer will result in no fragment shader :)
#else

	specular_light*=reflection_multiplier;

#ifdef USE_MULTIPLE_RENDER_TARGETS

	//approximate ambient scale for SSAO, since we will lack full ambient
	float max_ambient=max(ambient_light.r,max(ambient_light.g,ambient_light.b));
	float max_diffuse=max(diffuse_light.r,max(diffuse_light.g,diffuse_light.b));
	float total_ambient = max_ambient+max_diffuse;
	float ambient_scale = (total_ambient>0.0) ? max_ambient/total_ambient : 0.0;

	diffuse_buffer=vec4(diffuse_light+ambient_light,ambient_scale);
	specular_buffer=vec4(specular_light,0.0);
	normal_mr_buffer=vec4(normal.x,normal.y,max(specular.r,max(specular.g,specular.b)),roughness);

#else


#ifdef SHADELESS
	frag_color=vec4(albedo,alpha);
#else
	frag_color=vec4(ambient_light+diffuse_light+specular_light,alpha);
#endif //SHADELESS

#endif //USE_MULTIPLE_RENDER_TARGETS

#endif //RENDER_SHADOW


}


