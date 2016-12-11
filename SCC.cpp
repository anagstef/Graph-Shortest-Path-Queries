#include "SCC.h"

SCC::SCC() {
    comps_size = COMPONENTS;
    components = (Component*) malloc(comps_size * sizeof(Component));
    components_count = 0;
    id_belongs_to_component = (uint32_t*) malloc(comps_size * sizeof(uint32_t));
}

SCC::~SCC() {
    free(components);
    free(id_belongs_to_component);
}

void SCC::estimateStronglyConnectedComponents(Graph graph) {
    
}
