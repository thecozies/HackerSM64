extern Lights1 wmotr_dl_down_instant_warp_lights;
extern Vtx wmotr_dl_main_silo_mesh_vtx_2[154];
extern Vtx wmotr_dl_chamber_10_001_mesh_vtx_0[134];

static void shade_lights(Lights1* light, int amt)
{
    light->a.l.col[0]   += amt;
    light->a.l.col[1]   += amt;
    light->a.l.col[2]   += amt;
    light->a.l.colc[0]  += amt;
    light->a.l.colc[1]  += amt;
    light->a.l.colc[2]  += amt;
    light->l->l.col[0]  += 2*amt;
    light->l->l.col[1]  += 2*amt;
    light->l->l.col[2]  += 2*amt;
    light->l->l.colc[0] += 2*amt;
    light->l->l.colc[1] += 2*amt;
    light->l->l.colc[2] += 2*amt;
}


static void shade_vcols(Vtx* vtx, int cnt, int amt)
{
    for (int i = 0; i < cnt; i++)
    {
        vtx[i].v.cn[0] += amt;
        vtx[i].v.cn[1] += amt;
        vtx[i].v.cn[2] += amt;
    }
}

int count;

void bhv_dnvic_color_reset_init(void) {
    count = 0;
}

void bhv_dnvic_color_reset_loop(void) {
    if(count < 20) {
        Lights1* l0 = (Lights1*) segmented_to_virtual(&wmotr_dl_down_instant_warp_lights);
        shade_lights(l0, 2);
        Vtx* v0 = (Vtx*) segmented_to_virtual(wmotr_dl_main_silo_mesh_vtx_2);
        Vtx* v1 = (Vtx*) segmented_to_virtual(wmotr_dl_chamber_10_001_mesh_vtx_0); // chamber 10
        shade_vcols(v0, sizeof(wmotr_dl_main_silo_mesh_vtx_2) / sizeof(*wmotr_dl_main_silo_mesh_vtx_2), 3);
        shade_vcols(v1, sizeof(wmotr_dl_chamber_10_001_mesh_vtx_0) / sizeof(*wmotr_dl_chamber_10_001_mesh_vtx_0), 3);
        count += 1;
    }

}