#ifndef GIPROBE_H
#define GIPROBE_H

#include "scene/3d/visual_instance.h"
#include "multimesh_instance.h"

class GIProbeData : public Resource {

	OBJ_TYPE(GIProbeData,Resource);

	RID probe;

protected:

	static void _bind_methods();
public:



	void set_bounds(const AABB& p_bounds);
	AABB get_bounds() const;

	void set_cell_size(float p_size);
	float get_cell_size() const;

	void set_to_cell_xform(const Transform& p_xform);
	Transform get_to_cell_xform() const;

	void set_dynamic_data(const DVector<int>& p_data);
	DVector<int> get_dynamic_data() const;

	void set_dynamic_range(int p_range);
	int get_dynamic_range() const;

	void set_energy(float p_range);
	float get_energy() const;

	void set_interior(bool p_enable);
	bool is_interior() const;

	virtual RID get_rid() const;

	GIProbeData();
	~GIProbeData();
};



class GIProbe : public VisualInstance  {
	OBJ_TYPE(GIProbe,VisualInstance);
public:
	enum Subdiv{
		SUBDIV_64,
		SUBDIV_128,
		SUBDIV_256,
		SUBDIV_512,
		SUBDIV_MAX

	};
private:

	//stuff used for bake
	struct Baker {

		enum {
			CHILD_EMPTY=0xFFFFFFFF
		};
		struct Cell {

			uint32_t childs[8];
			float albedo[3]; //albedo in RGB24
			float emission[3]; //accumulated light in 16:16 fixed point (needs to be integer for moving lights fast)
			float normal[3];
			uint32_t used_sides;
			float alpha; //used for upsampling

			Cell() {
				for(int i=0;i<8;i++) {
					childs[i]=CHILD_EMPTY;
				}

				for(int i=0;i<3;i++) {
					emission[i]=0;
					albedo[i]=0;
					normal[i]=0;
				}
				alpha=0;
				used_sides=0;
			}
		};

		Vector<Cell> bake_cells;
		int cell_subdiv;

		struct MaterialCache {
			//128x128 textures
			Vector<Color> albedo;
			Vector<Color> emission;
		};


		Vector<Color> _get_bake_texture(Image &p_image, const Color &p_color);
		Map<Ref<Material>,MaterialCache> material_cache;
		MaterialCache _get_material_cache(Ref<Material> p_material);
		int leaf_voxel_count;


		AABB po2_bounds;
		int axis_cell_size[3];

		struct PlotMesh {
			Ref<Mesh> mesh;
			Transform local_xform;
		};

		Transform to_cell_space;

		List<PlotMesh> mesh_list;
	};


	Ref<GIProbeData> probe_data;

	RID gi_probe;

	Subdiv subdiv;
	Vector3 extents;
	int dynamic_range;
	float energy;
	bool interior;

	int color_scan_cell_width;
	int bake_texture_size;

	Vector<Color> _get_bake_texture(Image &p_image,const Color& p_color);
	Baker::MaterialCache _get_material_cache(Ref<Material> p_material,Baker *p_baker);
	void _plot_face(int p_idx, int p_level, int p_x,int p_y,int p_z,const Vector3 *p_vtx, const Vector2* p_uv, const Baker::MaterialCache& p_material, const AABB &p_aabb,Baker *p_baker);
	void _plot_mesh(const Transform& p_xform, Ref<Mesh>& p_mesh, Baker *p_baker);
	void _find_meshes(Node *p_at_node,Baker *p_baker);
	void _fixup_plot(int p_idx, int p_level,int p_x,int p_y, int p_z,Baker *p_baker);

	void _debug_mesh(int p_idx, int p_level, const AABB &p_aabb,Ref<MultiMesh> &p_multimesh,int &idx,Baker *p_baker);
	void _create_debug_mesh(Baker *p_baker);

	void _debug_bake();

protected:

	static void _bind_methods();
public:

	void set_probe_data(const Ref<GIProbeData>& p_data);
	Ref<GIProbeData> get_probe_data() const;

	void set_subdiv(Subdiv p_subdiv);
	Subdiv get_subdiv() const;

	void set_extents(const Vector3& p_extents);
	Vector3 get_extents() const;

	void set_dynamic_range(int p_dynamic_range);
	int get_dynamic_range() const;

	void set_energy(float p_energy);
	float get_energy() const;

	void set_interior(bool p_enable);
	bool is_interior() const;


	void bake(Node *p_from_node=NULL,bool p_create_visual_debug=false);

	virtual AABB get_aabb() const;
	virtual DVector<Face3> get_faces(uint32_t p_usage_flags) const;

	GIProbe();
	~GIProbe();
};

VARIANT_ENUM_CAST(GIProbe::Subdiv)

#endif // GIPROBE_H
