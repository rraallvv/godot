/*************************************************************************/
/*  resource.h                                                           */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                    http://www.godotengine.org                         */
/*************************************************************************/
/* Copyright (c) 2007-2017 Juan Linietsky, Ariel Manzur.                 */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
#ifndef RESOURCE_H
#define RESOURCE_H

#include "object.h"
#include "safe_refcount.h"
#include "ref_ptr.h"
#include "reference.h"
#include "object_type_db.h"

/**
	@author Juan Linietsky <reduzio@gmail.com>
*/

#define RES_BASE_EXTENSION(m_ext)\
public:\
static void register_custom_data_to_otdb() { ClassDB::add_resource_base_extension(m_ext,get_class_static()); }\
virtual String get_base_extension() const { return m_ext; }\
private:


class ResourceImportMetadata : public Reference {

	GDCLASS( ResourceImportMetadata, Reference );

	struct Source {
		String path;
		String md5;
	};

	Vector<Source> sources;
	String editor;

	Map<String,Variant> options;

	StringArray _get_options() const;

protected:

	static void _bind_methods();
public:

	void set_editor(const String& p_editor);
	String get_editor() const;

	void add_source(const String& p_path,const String& p_md5="");
	String get_source_path(int p_idx) const;
	String get_source_md5(int p_idx) const;
	void set_source_md5(int p_idx,const String& p_md5);
	void remove_source(int p_idx);
	int get_source_count() const;

	void set_option(const String& p_key, const Variant& p_value);
	Variant get_option(const String& p_key) const;
	bool has_option(const String& p_key) const;

	void get_options(List<String> *r_options) const;


	ResourceImportMetadata();
};


class Resource : public Reference {

	GDCLASS( Resource, Reference );
	OBJ_CATEGORY("Resources");
	RES_BASE_EXTENSION("res");

	Set<ObjectID> owners;

friend class ResBase;
friend class ResourceCache;

	String name;
	String path_cache;
	int subindex;

	virtual bool _use_builtin_script() const { return true; }

#ifdef TOOLS_ENABLED
	Ref<ResourceImportMetadata> import_metadata;
	uint64_t last_modified_time;
#endif

	bool local_to_scene;
friend class SceneState;
	Node* local_scene;

protected:

	void emit_changed();

	void notify_change_to_owners();

	virtual void _resource_path_changed();
	static void _bind_methods();

	void _set_path(const String& p_path);
	void _take_over_path(const String& p_path);
public:

	static Node* (*_get_local_scene_func)(); //used by editor

	virtual bool editor_can_reload_from_file();
	virtual void reload_from_file();

	void register_owner(Object *p_owner);
	void unregister_owner(Object *p_owner);

	void set_name(const String& p_name);
	String get_name() const;

	virtual void set_path(const String& p_path,bool p_take_over=false);
	String get_path() const;

	void set_subindex(int p_sub_index);
	int get_subindex() const;

	Ref<Resource> duplicate(bool p_subresources=false);
	Ref<Resource> duplicate_for_local_scene(Node *p_scene,Map<Ref<Resource>,Ref<Resource> >& remap_cache);


	void set_import_metadata(const Ref<ResourceImportMetadata>& p_metadata);
	Ref<ResourceImportMetadata> get_import_metadata() const;

	void set_local_to_scene(bool p_enable);
	bool is_local_to_scene() const;
	virtual void setup_local_to_scene();

	Node* get_local_scene() const;

#ifdef TOOLS_ENABLED

	uint32_t hash_edited_version() const;

	virtual void set_last_modified_time(uint64_t p_time) { last_modified_time=p_time; }
	uint64_t get_last_modified_time() const { return last_modified_time; }

#endif

	virtual RID get_rid() const; // some resources may offer conversion to RID

	Resource();
	~Resource();

};


typedef Ref<Resource> RES;

class ResourceCache {
friend class Resource;
	static RWLock *lock;
	static HashMap<String,Resource*> resources;
friend void unregister_core_types();
	static void clear();
friend void register_core_types();
	static void setup();
public:

	static void reload_externals();
	static bool has(const String& p_path);
	static Resource* get(const String& p_path);
	static void dump(const char* p_file=NULL,bool p_short=false);
	static void get_cached_resources(List<Ref<Resource> > *p_resources);
	static int get_cached_resource_count();

};

#endif
