#ifndef SPLIT_INDEX_H
#define SPLIT_INDEX_H

struct index_state;
struct strbuf;
struct ewah_bitmap;

struct split_index {
	unsigned char base_sha1[20];
	struct index_state *base;
	struct ewah_bitmap *delete_bitmap;
	struct ewah_bitmap *replace_bitmap;
	struct cache_entry **saved_cache;
	unsigned int saved_cache_nr;
	unsigned int nr_deletions;
	unsigned int nr_replacements;
	int refcount;
};

struct split_index *init_split_index(struct index_state *istate);
void save_or_free_index_entry(struct index_state *istate, struct cache_entry *ce);
void replace_index_entry_in_base(struct index_state *istate,
				 struct cache_entry *old,
				 struct cache_entry *new);
int read_link_extension(struct index_state *istate,
			const void *data, unsigned long sz);
int write_link_extension(struct strbuf *sb,
			 struct index_state *istate);
void move_cache_to_base_index(struct index_state *istate);
void merge_base_index(struct index_state *istate);
void prepare_to_write_split_index(struct index_state *istate);
void finish_writing_split_index(struct index_state *istate);
void discard_split_index(struct index_state *istate);
void add_split_index(struct index_state *istate);
void remove_split_index(struct index_state *istate);
void unshare_split_index(struct index_state *istate, int discard);

#endif
