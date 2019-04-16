/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WindowInterface.h
 * Author: sssililliths
 *
 */

#ifndef WINDOWINTERFACE_H
#define WINDOWINTERFACE_H

const std::string gMainWindow = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generated with glade 3.22.1 -->\
<interface>\
  <requires lib=\"gtk+\" version=\"3.10\"/>\
  <object class=\"GtkImage\" id=\"imgLoadMore\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"icon_name\">folder-new</property>\
  </object>\
  <object class=\"GtkImage\" id=\"imgMainComment\">\
    <property name=\"visible\">True</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"icon_name\">insert-text</property>\
  </object>\
  <object class=\"GtkApplicationWindow\" id=\"wndAppWindow\">\
    <property name=\"width_request\">400</property>\
    <property name=\"height_request\">300</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"title\" translatable=\"yes\">Visual sudo configurator</property>\
    <property name=\"window_position\">center</property>\
    <child>\
      <placeholder/>\
    </child>\
    <child>\
      <object class=\"GtkBox\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkMenuBar\" id=\"mnbMainMenu\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkMenuItem\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">_File</property>\
                <property name=\"use_underline\">True</property>\
                <child type=\"submenu\">\
                  <object class=\"GtkMenu\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <child>\
                      <object class=\"GtkImageMenuItem\" id=\"imiOpen\">\
                        <property name=\"label\">Open</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"use_underline\">True</property>\
                        <property name=\"use_stock\">True</property>\
                      </object>\
                    </child>\
                    <child>\
                      <object class=\"GtkImageMenuItem\" id=\"imiOpenMore\">\
                        <property name=\"label\">Open more</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"image\">imgLoadMore</property>\
                        <property name=\"use_stock\">False</property>\
                      </object>\
                    </child>\
                    <child>\
                      <object class=\"GtkImageMenuItem\" id=\"imiSave\">\
                        <property name=\"label\">Save</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"use_underline\">True</property>\
                        <property name=\"use_stock\">True</property>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
              </object>\
            </child>\
            <child>\
              <object class=\"GtkMenuItem\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">_Edit</property>\
                <property name=\"use_underline\">True</property>\
                <child type=\"submenu\">\
                  <object class=\"GtkMenu\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <child>\
                      <object class=\"GtkImageMenuItem\" id=\"imiMainComment\">\
                        <property name=\"label\">Main comment</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"image\">imgMainComment</property>\
                        <property name=\"use_stock\">False</property>\
                      </object>\
                    </child>\
                    <child>\
                      <object class=\"GtkImageMenuItem\" id=\"imiDefaults\">\
                        <property name=\"label\">About</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"use_underline\">True</property>\
                        <property name=\"use_stock\">True</property>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
              </object>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkNotebook\" id=\"ntbDataCategories\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">True</property>\
            <property name=\"scrollable\">True</property>\
            <property name=\"enable_popup\">True</property>\
            <child>\
              <object class=\"GtkFrame\" id=\"frmUser\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">none</property>\
                <child>\
                  <object class=\"GtkAlignment\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkScrolledWindow\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkTreeView\" id=\"trvUserData\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <child internal-child=\"selection\">\
                                  <object class=\"GtkTreeSelection\"/>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkSearchEntry\" id=\"srcUser\">\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"editable\">False</property>\
                                <property name=\"visibility\">False</property>\
                                <property name=\"primary_icon_name\">edit-find-symbolic</property>\
                                <property name=\"primary_icon_activatable\">False</property>\
                                <property name=\"primary_icon_sensitive\">False</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButtonBox\" id=\"btbUserMenu\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"layout_style\">start</property>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnUserAdd\">\
                                    <property name=\"label\" translatable=\"yes\">Add</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnUserModify\">\
                                    <property name=\"label\" translatable=\"yes\">Modify</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnUserRemove\">\
                                    <property name=\"label\" translatable=\"yes\">Remove</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                </child>\
              </object>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"lblUsersPage\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Users</property>\
              </object>\
              <packing>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frmDefaults\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">none</property>\
                <child>\
                  <object class=\"GtkAlignment\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkScrolledWindow\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkTreeView\" id=\"trvDefaultsData\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <child internal-child=\"selection\">\
                                  <object class=\"GtkTreeSelection\"/>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkSearchEntry\" id=\"srcAlias1\">\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"editable\">False</property>\
                                <property name=\"visibility\">False</property>\
                                <property name=\"primary_icon_name\">edit-find-symbolic</property>\
                                <property name=\"primary_icon_activatable\">False</property>\
                                <property name=\"primary_icon_sensitive\">False</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButtonBox\" id=\"btbUserMenu1\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"layout_style\">start</property>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnDefaultsAdd\">\
                                    <property name=\"label\" translatable=\"yes\">Add</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnDefaultsModify\">\
                                    <property name=\"label\" translatable=\"yes\">Modify</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnDefaultsRemove\">\
                                    <property name=\"label\" translatable=\"yes\">Remove</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Defaults</property>\
              </object>\
              <packing>\
                <property name=\"position\">1</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkFrame\" id=\"frmAlias\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label_xalign\">0</property>\
                <property name=\"shadow_type\">none</property>\
                <child>\
                  <object class=\"GtkAlignment\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"left_padding\">12</property>\
                    <child>\
                      <object class=\"GtkBox\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkScrolledWindow\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"shadow_type\">in</property>\
                            <child>\
                              <object class=\"GtkTreeView\" id=\"trvAliasData\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">True</property>\
                                <child internal-child=\"selection\">\
                                  <object class=\"GtkTreeSelection\"/>\
                                </child>\
                              </object>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkBox\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"orientation\">vertical</property>\
                            <child>\
                              <object class=\"GtkSearchEntry\" id=\"srcAlias\">\
                                <property name=\"can_focus\">True</property>\
                                <property name=\"editable\">False</property>\
                                <property name=\"visibility\">False</property>\
                                <property name=\"primary_icon_name\">edit-find-symbolic</property>\
                                <property name=\"primary_icon_activatable\">False</property>\
                                <property name=\"primary_icon_sensitive\">False</property>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">0</property>\
                              </packing>\
                            </child>\
                            <child>\
                              <object class=\"GtkButtonBox\" id=\"btbUserMenu2\">\
                                <property name=\"visible\">True</property>\
                                <property name=\"can_focus\">False</property>\
                                <property name=\"orientation\">vertical</property>\
                                <property name=\"layout_style\">start</property>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnAliasAdd\">\
                                    <property name=\"label\" translatable=\"yes\">Add</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">0</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnAliasModify\">\
                                    <property name=\"label\" translatable=\"yes\">Modify</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">1</property>\
                                  </packing>\
                                </child>\
                                <child>\
                                  <object class=\"GtkButton\" id=\"btnAliasRemove\">\
                                    <property name=\"label\" translatable=\"yes\">Remove</property>\
                                    <property name=\"visible\">True</property>\
                                    <property name=\"can_focus\">True</property>\
                                    <property name=\"receives_default\">True</property>\
                                    <property name=\"margin_top\">3</property>\
                                    <property name=\"margin_bottom\">3</property>\
                                  </object>\
                                  <packing>\
                                    <property name=\"expand\">True</property>\
                                    <property name=\"fill\">True</property>\
                                    <property name=\"position\">2</property>\
                                  </packing>\
                                </child>\
                              </object>\
                              <packing>\
                                <property name=\"expand\">False</property>\
                                <property name=\"fill\">True</property>\
                                <property name=\"position\">1</property>\
                              </packing>\
                            </child>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                    </child>\
                  </object>\
                </child>\
                <child type=\"label\">\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                  </object>\
                </child>\
              </object>\
              <packing>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child type=\"tab\">\
              <object class=\"GtkLabel\" id=\"lblAliasesPage\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"label\" translatable=\"yes\">Aliases</property>\
              </object>\
              <packing>\
                <property name=\"position\">2</property>\
                <property name=\"tab_fill\">False</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
</interface>";


const std::string gUserWindow = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generated with glade 3.22.1 -->\
<interface>\
  <requires lib=\"gtk+\" version=\"3.20\"/>\
  <object class=\"GtkWindow\" id=\"wndUserEdit\">\
    <property name=\"name\">wndUserWindow</property>\
    <property name=\"can_focus\">False</property>\
    <property name=\"window_position\">center-on-parent</property>\
    <property name=\"gravity\">center</property>\
    <child>\
      <placeholder/>\
    </child>\
    <child>\
      <object class=\"GtkBox\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">7</property>\
                <property name=\"margin_right\">4</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Name</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtName\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">3</property>\
                    <child>\
                      <object class=\"GtkCheckButton\" id=\"ckbNameFromAlias\">\
                        <property name=\"label\" translatable=\"yes\">Alias</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">False</property>\
                        <property name=\"draw_indicator\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkComboBox\" id=\"cmbNameAlias\">\
                        <property name=\"can_focus\">False</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">4</property>\
                <property name=\"margin_right\">4</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Host</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtHost\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">3</property>\
                    <child>\
                      <object class=\"GtkCheckButton\" id=\"ckbHostFromAlias\">\
                        <property name=\"label\" translatable=\"yes\">Alias</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">False</property>\
                        <property name=\"draw_indicator\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkComboBox\" id=\"cmbHostAlias\">\
                        <property name=\"can_focus\">False</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">4</property>\
                <property name=\"margin_right\">4</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">RunAs</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtRunas\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">3</property>\
                    <child>\
                      <object class=\"GtkCheckButton\" id=\"ckbRunasFromAlias\">\
                        <property name=\"label\" translatable=\"yes\">Alias</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">False</property>\
                        <property name=\"draw_indicator\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkComboBox\" id=\"cmbRunasAlias\">\
                        <property name=\"can_focus\">False</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">True</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">8</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Cmds</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkTreeView\" id=\"trvCmds\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"margin_top\">2</property>\
                    <property name=\"margin_bottom\">2</property>\
                    <child internal-child=\"selection\">\
                      <object class=\"GtkTreeSelection\"/>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">2</property>\
                    <property name=\"margin_bottom\">2</property>\
                    <property name=\"orientation\">vertical</property>\
                    <child>\
                      <object class=\"GtkBox\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <child>\
                          <object class=\"GtkComboBoxText\" id=\"cmbCmdOption\">\
                            <property name=\"can_focus\">False</property>\
                            <property name=\"margin_right\">3</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkEntry\" id=\"txtCmds\">\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"margin_right\">2</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkButton\" id=\"btnAdd\">\
                            <property name=\"label\" translatable=\"yes\">+</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"receives_default\">True</property>\
                            <property name=\"margin_left\">2</property>\
                            <property name=\"margin_right\">2</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">2</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkButton\" id=\"btnRemove\">\
                            <property name=\"label\" translatable=\"yes\">-</property>\
                            <property name=\"visible\">True</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"receives_default\">True</property>\
                            <property name=\"margin_left\">2</property>\
                            <property name=\"margin_right\">2</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">3</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkBox\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_top\">2</property>\
                        <child>\
                          <object class=\"GtkCheckButton\" id=\"ckbCmdFromAlias\">\
                            <property name=\"label\" translatable=\"yes\">Alias</property>\
                            <property name=\"can_focus\">True</property>\
                            <property name=\"receives_default\">False</property>\
                            <property name=\"draw_indicator\">True</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">False</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">0</property>\
                          </packing>\
                        </child>\
                        <child>\
                          <object class=\"GtkComboBox\" id=\"cmbCmdsAlias\">\
                            <property name=\"can_focus\">False</property>\
                          </object>\
                          <packing>\
                            <property name=\"expand\">True</property>\
                            <property name=\"fill\">True</property>\
                            <property name=\"position\">1</property>\
                          </packing>\
                        </child>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"label\" translatable=\"yes\">Comment</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkTextView\" id=\"txtComment\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkButtonBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_right\">10</property>\
            <property name=\"margin_top\">5</property>\
            <property name=\"margin_bottom\">5</property>\
            <property name=\"spacing\">10</property>\
            <property name=\"baseline_position\">bottom</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkEntry\" id=\"txtId\">\
                <property name=\"can_focus\">True</property>\
                <property name=\"editable\">False</property>\
                <property name=\"visibility\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkCheckButton\" id=\"chkIsGroup\">\
                <property name=\"label\" translatable=\"yes\">Group</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">False</property>\
                <property name=\"margin_right\">538</property>\
                <property name=\"draw_indicator\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnSave\">\
                <property name=\"label\" translatable=\"yes\">Save</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnCancel\">\
                <property name=\"label\" translatable=\"yes\">Cancel</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
</interface>";

const std::string gAliasWindow =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generated with glade 3.22.1 -->\
<interface>\
  <requires lib=\"gtk+\" version=\"3.20\"/>\
  <object class=\"GtkWindow\" id=\"wndAliasEdit\">\
    <property name=\"can_focus\">False</property>\
    <property name=\"window_position\">center-on-parent</property>\
    <property name=\"gravity\">center</property>\
    <child>\
      <placeholder/>\
    </child>\
    <child>\
      <object class=\"GtkBox\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"halign\">center</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Type</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"cmbType\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"halign\">center</property>\
                    <property name=\"valign\">center</property>\
                    <property name=\"margin_top\">28</property>\
                    <property name=\"margin_bottom\">9</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"halign\">center</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"label\" translatable=\"yes\">Name</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtName\">\
                    <property name=\"name\">txtName</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"padding\">30</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"halign\">center</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"margin_top\">7</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkTreeView\" id=\"trvCmds\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"margin_right\">13</property>\
                    <property name=\"margin_bottom\">7</property>\
                    <child internal-child=\"selection\">\
                      <object class=\"GtkTreeSelection\"/>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">True</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkBox\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <child>\
                      <object class=\"GtkComboBoxText\" id=\"cmbCmdOption\">\
                        <property name=\"can_focus\">False</property>\
                        <property name=\"margin_right\">3</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">0</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkEntry\" id=\"txtCmd\">\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"margin_right\">7</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">1</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btnAdd\">\
                        <property name=\"label\" translatable=\"yes\">+</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">2</property>\
                      </packing>\
                    </child>\
                    <child>\
                      <object class=\"GtkButton\" id=\"btnRemove\">\
                        <property name=\"label\" translatable=\"yes\">-</property>\
                        <property name=\"visible\">True</property>\
                        <property name=\"can_focus\">True</property>\
                        <property name=\"receives_default\">True</property>\
                        <property name=\"margin_left\">5</property>\
                      </object>\
                      <packing>\
                        <property name=\"expand\">False</property>\
                        <property name=\"fill\">True</property>\
                        <property name=\"position\">3</property>\
                      </packing>\
                    </child>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"pack_type\">end</property>\
                    <property name=\"position\">2</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkButtonBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_right\">5</property>\
            <property name=\"spacing\">10</property>\
            <property name=\"baseline_position\">bottom</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkEntry\" id=\"txtId\">\
                <property name=\"can_focus\">True</property>\
                <property name=\"editable\">False</property>\
                <property name=\"visibility\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnSave\">\
                <property name=\"label\" translatable=\"yes\">Save</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnCancel\">\
                <property name=\"label\" translatable=\"yes\">Cancel</property>\
                <property name=\"name\">btnCancel</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
                <property name=\"margin_right\">15</property>\
                <property name=\"resize_mode\">immediate</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"padding\">2</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"padding\">9</property>\
            <property name=\"pack_type\">end</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"margin_top\">5</property>\
            <child>\
              <object class=\"GtkLabel\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"label\" translatable=\"yes\">Comment</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkTextView\" id=\"txtComment\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">5</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
</interface>";

const std::string gDefaultsWindow = 
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<!-- Generated with glade 3.22.1 -->\
<interface>\
  <requires lib=\"gtk+\" version=\"3.20\"/>\
  <object class=\"GtkWindow\" id=\"wndDefaultsEdit\">\
    <property name=\"can_focus\">False</property>\
    <child>\
      <placeholder/>\
    </child>\
    <child>\
      <object class=\"GtkBox\">\
        <property name=\"visible\">True</property>\
        <property name=\"can_focus\">False</property>\
        <property name=\"orientation\">vertical</property>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"label\" translatable=\"yes\">Type</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"cmbType\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">3</property>\
                    <property name=\"margin_top\">10</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"boxOwner\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"label\" translatable=\"yes\">Owner</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtOwner\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">3</property>\
                    <property name=\"margin_top\">10</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"label\" translatable=\"yes\">Parameter</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"cmbParameter\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">2</property>\
                    <property name=\"margin_top\">10</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">2</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"label\" translatable=\"yes\">Method</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkComboBoxText\" id=\"cmbMethod\">\
                    <property name=\"name\">cmbMethod</property>\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">10</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkBox\" id=\"boxValues\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"orientation\">vertical</property>\
                <child>\
                  <object class=\"GtkLabel\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">False</property>\
                    <property name=\"margin_top\">5</property>\
                    <property name=\"label\" translatable=\"yes\">Values</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">0</property>\
                  </packing>\
                </child>\
                <child>\
                  <object class=\"GtkEntry\" id=\"txtValue\">\
                    <property name=\"visible\">True</property>\
                    <property name=\"can_focus\">True</property>\
                    <property name=\"margin_left\">5</property>\
                    <property name=\"margin_right\">5</property>\
                    <property name=\"margin_top\">10</property>\
                    <property name=\"margin_bottom\">5</property>\
                  </object>\
                  <packing>\
                    <property name=\"expand\">False</property>\
                    <property name=\"fill\">True</property>\
                    <property name=\"position\">1</property>\
                  </packing>\
                </child>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">3</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">True</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">0</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <child>\
              <object class=\"GtkLabel\" id=\"lblComment\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">False</property>\
                <property name=\"margin_left\">10</property>\
                <property name=\"margin_right\">5</property>\
                <property name=\"label\" translatable=\"yes\">Comment</property>\
              </object>\
              <packing>\
                <property name=\"expand\">False</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkTextView\" id=\"txtComment\">\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"margin_left\">5</property>\
                <property name=\"margin_right\">10</property>\
                <property name=\"margin_top\">2</property>\
                <property name=\"margin_bottom\">5</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">1</property>\
          </packing>\
        </child>\
        <child>\
          <object class=\"GtkButtonBox\">\
            <property name=\"visible\">True</property>\
            <property name=\"can_focus\">False</property>\
            <property name=\"spacing\">10</property>\
            <property name=\"layout_style\">end</property>\
            <child>\
              <object class=\"GtkEntry\" id=\"txtId\">\
                <property name=\"can_focus\">True</property>\
                <property name=\"editable\">False</property>\
                <property name=\"visibility\">False</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnSave\">\
                <property name=\"label\" translatable=\"yes\">Save</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">0</property>\
              </packing>\
            </child>\
            <child>\
              <object class=\"GtkButton\" id=\"btnCancel\">\
                <property name=\"label\" translatable=\"yes\">Cancel</property>\
                <property name=\"visible\">True</property>\
                <property name=\"can_focus\">True</property>\
                <property name=\"receives_default\">True</property>\
              </object>\
              <packing>\
                <property name=\"expand\">True</property>\
                <property name=\"fill\">True</property>\
                <property name=\"position\">1</property>\
              </packing>\
            </child>\
          </object>\
          <packing>\
            <property name=\"expand\">False</property>\
            <property name=\"fill\">True</property>\
            <property name=\"position\">2</property>\
          </packing>\
        </child>\
      </object>\
    </child>\
  </object>\
</interface>";

#endif /* WINDOWINTERFACE_H */

