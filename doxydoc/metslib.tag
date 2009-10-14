<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>main</name>
    <title>METSlib</title>
    <filename>main</filename>
    <docanchor file="main">Introduction</docanchor>
  </compound>
  <compound kind="group">
    <name>model</name>
    <title>Model</title>
    <filename>a00035.html</filename>
    <class kind="class">mets::feasible_solution</class>
    <class kind="class">mets::move</class>
    <class kind="class">mets::mana_move</class>
    <class kind="class">mets::complex_mana_move</class>
    <class kind="class">mets::move_manager</class>
  </compound>
  <compound kind="group">
    <name>common</name>
    <title>Common pieces</title>
    <filename>a00036.html</filename>
    <class kind="class">mets::termination_criteria_chain</class>
    <class kind="class">mets::search_listener</class>
    <class kind="class">mets::iteration_termination_criteria</class>
    <class kind="class">mets::noimprove_termination_criteria</class>
    <class kind="class">mets::threshold_termination_criteria</class>
  </compound>
  <compound kind="group">
    <name>local_search</name>
    <title>Local Search</title>
    <filename>a00037.html</filename>
    <class kind="class">mets::local_search</class>
  </compound>
  <compound kind="group">
    <name>simulated_annealing</name>
    <title>Simulated Annealing</title>
    <filename>a00038.html</filename>
    <class kind="class">mets::abstract_cooling_schedule</class>
    <class kind="class">mets::simulated_annealing</class>
    <class kind="class">mets::exponential_cooling</class>
    <class kind="class">mets::linear_cooling</class>
  </compound>
  <compound kind="group">
    <name>tabu_search</name>
    <title>Tabu Search</title>
    <filename>a00039.html</filename>
    <class kind="class">mets::aspiration_criteria_chain</class>
    <class kind="class">mets::tabu_list_chain</class>
    <class kind="class">mets::tabu_search</class>
    <class kind="class">mets::simple_tabu_list</class>
    <class kind="class">mets::best_ever_criteria</class>
  </compound>
  <compound kind="namespace">
    <name>mets</name>
    <filename>a00033.html</filename>
    <class kind="class">mets::no_moves_error</class>
    <class kind="class">mets::sequence</class>
    <class kind="class">mets::feasible_solution</class>
    <class kind="class">mets::move</class>
    <class kind="class">mets::mana_move</class>
    <class kind="class">mets::complex_mana_move</class>
    <class kind="class">mets::move_manager</class>
    <class kind="class">mets::mana_move_hash</class>
    <class kind="struct">mets::dereferenced_equal_to</class>
    <class kind="class">mets::termination_criteria_chain</class>
    <class kind="class">mets::search_listener</class>
    <class kind="class">mets::abstract_search</class>
    <class kind="class">mets::local_search</class>
    <class kind="class">mets::abstract_cooling_schedule</class>
    <class kind="class">mets::simulated_annealing</class>
    <class kind="class">mets::exponential_cooling</class>
    <class kind="class">mets::linear_cooling</class>
    <class kind="class">mets::aspiration_criteria_chain</class>
    <class kind="class">mets::tabu_list_chain</class>
    <class kind="class">mets::tabu_search</class>
    <class kind="class">mets::simple_tabu_list</class>
    <class kind="class">mets::best_ever_criteria</class>
    <class kind="class">mets::iteration_termination_criteria</class>
    <class kind="class">mets::noimprove_termination_criteria</class>
    <class kind="class">mets::threshold_termination_criteria</class>
    <class kind="class">mets::update_observer</class>
    <class kind="class">mets::subject</class>
    <class kind="class">mets::observer</class>
    <member kind="typedef">
      <type>double</type>
      <name>gol_type</name>
      <anchorfile>a00033.html</anchorfile>
      <anchor>61116f509383ed86807529856bf4b333</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::no_moves_error</name>
    <filename>a00016.html</filename>
    <member kind="function">
      <type></type>
      <name>no_moves_error</name>
      <anchorfile>a00016.html</anchorfile>
      <anchor>f2bcf287df786fea96c332728721ab21</anchor>
      <arglist>(const std::string message)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::sequence</name>
    <filename>a00020.html</filename>
    <member kind="function">
      <type></type>
      <name>sequence</name>
      <anchorfile>a00020.html</anchorfile>
      <anchor>14177f4a3aa54c1611747ab44356307a</anchor>
      <arglist>(int start=0)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>operator()</name>
      <anchorfile>a00020.html</anchorfile>
      <anchor>8f6e2b7ee95d0c3295ac55e83c68d945</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>value_m</name>
      <anchorfile>a00020.html</anchorfile>
      <anchor>adb4b06f2bac6d9307d831cd59057454</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::feasible_solution</name>
    <filename>a00008.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~feasible_solution</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>b15b3260d5e1eec2a79e103347ca788f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual gol_type</type>
      <name>cost_function</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>03640fcd542e2039c417762920531de0</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>copy_from</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>8b626d6d2b971b1d2f1719c15a00d6a2</anchor>
      <arglist>(const feasible_solution &amp;other)=0</arglist>
    </member>
    <member kind="function">
      <type>feasible_solution &amp;</type>
      <name>operator=</name>
      <anchorfile>a00008.html</anchorfile>
      <anchor>3495777d254a485bbdc6da9c5afcb676</anchor>
      <arglist>(const feasible_solution &amp;other)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::move</name>
    <filename>a00014.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>apply</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>9e6bbe097efb6dca4d222f492d6486b6</anchor>
      <arglist>(feasible_solution &amp;sol)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>unapply</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>2d0299bcd06306372f1902a092cb8290</anchor>
      <arglist>(feasible_solution &amp;sol)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>print</name>
      <anchorfile>a00014.html</anchorfile>
      <anchor>3a2bb69e73249afcc621140710f4ec0e</anchor>
      <arglist>(ostream &amp;os) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::mana_move</name>
    <filename>a00012.html</filename>
    <base>mets::move</base>
    <member kind="function" virtualness="pure">
      <type>virtual mana_move *</type>
      <name>clone</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>dc7ca6e2560b70fd6f6826b3b99dc5dd</anchor>
      <arglist>() const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>operator==</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>7ff17d8c4ffa899dc3ba7279e7e829c0</anchor>
      <arglist>(const mana_move &amp;other) const =0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t</type>
      <name>hash</name>
      <anchorfile>a00012.html</anchorfile>
      <anchor>91cf513dc165994f0de894a331e2edcd</anchor>
      <arglist>() const =0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::complex_mana_move</name>
    <filename>a00005.html</filename>
    <base>mets::mana_move</base>
    <member kind="function">
      <type></type>
      <name>complex_mana_move</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>54361ce8433c3c4dfb427ee1c48978e9</anchor>
      <arglist>(int n=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>complex_mana_move</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>15d8344a1e47d425373f55ce048b54eb</anchor>
      <arglist>(const complex_mana_move &amp;o)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~complex_mana_move</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>be70cc54c325100dc92230684b82a798</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>push_back</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>3f9c9f147cf9aa746bf52719baece19b</anchor>
      <arglist>(mana_move *m)</arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>size</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>7faaebab3bec228d1186764385f7966a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>mana_move *&amp;</type>
      <name>operator[]</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>f21372fff443d16819e5aa7c27f519d0</anchor>
      <arglist>(unsigned int ii)</arglist>
    </member>
    <member kind="function">
      <type>const mana_move *</type>
      <name>operator[]</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>5af9a8db08fe5dc11e93e327b9acca21</anchor>
      <arglist>(unsigned int ii) const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>apply</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>3158eb6b410687701d9b9577ff32b273</anchor>
      <arglist>(mets::feasible_solution &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>unapply</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>5a65d0470655aece8f1312b09efe23be</anchor>
      <arglist>(mets::feasible_solution &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>mana_move *</type>
      <name>clone</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>d867f3cc68108eb019a63382e71ed075</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>size_t</type>
      <name>hash</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>f62ff797e5bfd4ce685b644ecbc223b1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>c4569705f1474d2d23fa54c01a03fad1</anchor>
      <arglist>(const mana_move &amp;o) const </arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; mets::mana_move * &gt;</type>
      <name>move_list_t</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>a22f19db2e0e3eaf3ae599043148bf87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>move_list_t</type>
      <name>moves_m</name>
      <anchorfile>a00005.html</anchorfile>
      <anchor>ca6274d8a176d565e1ce68c713844ef5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::move_manager</name>
    <filename>a00015.html</filename>
    <member kind="typedef">
      <type>std::deque&lt; move * &gt;::iterator</type>
      <name>iterator</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>eefc958bebc97fe6b61ce19c0ef37f1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; move * &gt;::size_type</type>
      <name>size_type</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>fa4c4ed8f7f06f5b71d9bef68c11b36d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>move_manager</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>546406d667dc0d50b5e96ba9f26df457</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~move_manager</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>8043a2af47c32cd18d49549cc3075f26</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>refresh</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>4cbd79d0a14575695ee5590b67a482ba</anchor>
      <arglist>(feasible_solution &amp;sol)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual iterator</type>
      <name>begin</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>75f3a7d16cb0276097c441102ab6541b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual iterator</type>
      <name>end</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>780b34b675bdfeee5ca46a0e6c783d97</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual size_type</type>
      <name>size</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>e9cdbc90f29310f81bd634f1e864e959</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::deque&lt; move * &gt;</type>
      <name>moves_m</name>
      <anchorfile>a00015.html</anchorfile>
      <anchor>764ca3061b1f019b5508fc03323fd501</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::mana_move_hash</name>
    <filename>a00013.html</filename>
    <member kind="function">
      <type>size_t</type>
      <name>operator()</name>
      <anchorfile>a00013.html</anchorfile>
      <anchor>c0ceb9995dba5db46d57b413f11ebdf0</anchor>
      <arglist>(mana_move const *mov) const </arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>mets::dereferenced_equal_to</name>
    <filename>a00006.html</filename>
    <templarg>Tp</templarg>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00006.html</anchorfile>
      <anchor>139ffe605862929679580715b01a856e</anchor>
      <arglist>(const Tp l, const Tp r) const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::termination_criteria_chain</name>
    <filename>a00026.html</filename>
    <member kind="function">
      <type></type>
      <name>termination_criteria_chain</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>b8072803ee53f230d9f557e10f9640ea</anchor>
      <arglist>(termination_criteria_chain *next=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>termination_criteria_chain</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>86bef36bc517f2f4f81dcc5a110d065e</anchor>
      <arglist>(const termination_criteria_chain &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>termination_criteria_chain &amp;</type>
      <name>operator=</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>898d729273c4bfaa5f92a254541a03a9</anchor>
      <arglist>(const termination_criteria_chain &amp;other)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~termination_criteria_chain</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>0dfb2f9bc6e3ce2e66bed297f86880cb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>operator()</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>cf9801c5247c31cb7412cc1b226b71d8</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>reset</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>3838e3118707b14fbb13ed257d358b8a</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>termination_criteria_chain *</type>
      <name>next_m</name>
      <anchorfile>a00026.html</anchorfile>
      <anchor>accffc670c01236af30df2c2e05f5e3b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::search_listener</name>
    <filename>a00019.html</filename>
    <base>mets::observer</base>
    <member kind="function">
      <type></type>
      <name>search_listener</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>b8283abf7b74c195eb3736bd98db3706</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>search_listener</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>74a9660ac78a2e5e1f2e5252bb24715d</anchor>
      <arglist>(const search_listener &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>search_listener &amp;</type>
      <name>operator=</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>cd797b5faf576ed68cc86bbbec09fb75</anchor>
      <arglist>(const search_listener &amp;other)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~search_listener</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>01824c4ab70bba0588b1a4d3480021b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update</name>
      <anchorfile>a00019.html</anchorfile>
      <anchor>ec935bffbb027d85025a3517e36c81e3</anchor>
      <arglist>(abstract_search *algorithm)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::abstract_search</name>
    <filename>a00002.html</filename>
    <base>mets::subject</base>
    <member kind="function">
      <type></type>
      <name>abstract_search</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>45a91c5b7846df513fa2c298dc4df168</anchor>
      <arglist>(feasible_solution &amp;working, feasible_solution &amp;best_so_far, move_manager &amp;moveman)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>abstract_search</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>f4b5cf8a10b1c3c3ad8d9826bc23b8f2</anchor>
      <arglist>(const abstract_search &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~abstract_search</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>801cf5c9508d495a20e737455ab1f714</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>search</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>debf3da2c6be6f113cdc61a483c7ae2b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const feasible_solution &amp;</type>
      <name>best</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>1587b6ba6506c9e606a9b1cf0a6bce18</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const feasible_solution &amp;</type>
      <name>working</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>b3cdaa0bf73bb1f7a2505fe2cb6231a4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual feasible_solution &amp;</type>
      <name>working</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>fa91e6d8ed5ad36b6d2af03cafc6253a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const move &amp;</type>
      <name>current_move</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>56e88b0f09fb74a7d8176165a301fcfd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual move &amp;</type>
      <name>current_move</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>4cc688423a060f3d3b1f6c21395b3ddd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const move_manager &amp;</type>
      <name>get_move_manager</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>406bc45518861dde35147c18341c1ace</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>move_manager &amp;</type>
      <name>get_move_manager</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>087c362fedc0b02e933f84b5777dcaff</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual int</type>
      <name>step</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>e3530d66ac8574262ccec0fefc400892</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual gol_type</type>
      <name>best_cost</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>ee759e0bde7294b18b3271803bfc6e85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MOVE_MADE</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>6c95c3d3ae0efc1635662954fd6c947a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>IMPROVEMENT_MADE</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>44c6fb4377a8ff60f9e45d4fda988a34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>feasible_solution &amp;</type>
      <name>best_solution_m</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>3ca24260c142059f181308d0411386b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>feasible_solution &amp;</type>
      <name>working_solution_m</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>dee39d9cb01be5fef2f9e81cc27c6b23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>move_manager &amp;</type>
      <name>moves_m</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>cf13907525d5bbfa18663c4a6da0005e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>move_manager::iterator</type>
      <name>current_move_m</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>46205a3c14d051c68542ea90d699e73c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>step_m</name>
      <anchorfile>a00002.html</anchorfile>
      <anchor>0086a1ac4dd6ba760d1e334ea675855c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::local_search</name>
    <filename>a00011.html</filename>
    <base>mets::abstract_search</base>
    <member kind="function">
      <type></type>
      <name>local_search</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>762b75b536a277893219640d99a59737</anchor>
      <arglist>(feasible_solution &amp;starting_point, feasible_solution &amp;best_so_far, move_manager &amp;moveman, bool short_circuit=false)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>local_search</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>7f5d09b6ecc770711869100358d5bdbd</anchor>
      <arglist>(const local_search &amp;)</arglist>
    </member>
    <member kind="function">
      <type>local_search &amp;</type>
      <name>operator=</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>e648a2ca1e702729e25aa8817459c111</anchor>
      <arglist>(const local_search &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>search</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>d44d95ca592104d26cc99454c9cff634</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>short_circuit_m</name>
      <anchorfile>a00011.html</anchorfile>
      <anchor>c9e40ed4a15979f8eb19b24f0937d9a2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::abstract_cooling_schedule</name>
    <filename>a00001.html</filename>
    <member kind="function">
      <type></type>
      <name>abstract_cooling_schedule</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>a0cb8ac805aaf2efb1148dfb951ca3eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~abstract_cooling_schedule</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>9c0f63810de6b6d798c7bc0b06acf4c1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual double</type>
      <name>operator()</name>
      <anchorfile>a00001.html</anchorfile>
      <anchor>7e3d1088b37e5ea2711f11bbcd4b30d3</anchor>
      <arglist>(double temp, feasible_solution &amp;fs, abstract_search &amp;as)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::simulated_annealing</name>
    <filename>a00022.html</filename>
    <base>mets::abstract_search</base>
    <member kind="function">
      <type></type>
      <name>simulated_annealing</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>a7a31baeb0504a078b0d10a11100746c</anchor>
      <arglist>(feasible_solution &amp;starting_point, feasible_solution &amp;best_so_far, move_manager &amp;moveman, termination_criteria_chain &amp;tc, abstract_cooling_schedule &amp;cs, double starting_temp, double K=1.0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simulated_annealing</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>d2620b7948dabd30e9cd58b483941830</anchor>
      <arglist>(const simulated_annealing &amp;)</arglist>
    </member>
    <member kind="function">
      <type>simulated_annealing &amp;</type>
      <name>operator=</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>aee271950586774e1c30dd04ef317874</anchor>
      <arglist>(const simulated_annealing &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>search</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>94b568a04014900351f6ebbc088cb6a0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>current_temp</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>c2dc788ada023153c88a01cde28afc54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const abstract_cooling_schedule &amp;</type>
      <name>cooling_schedule</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>cd6f03b79a26bc8a403919c2648a865b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>termination_criteria_chain &amp;</type>
      <name>termination_criteria_m</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>5d2988090f75758e744396f0ce3370ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>abstract_cooling_schedule &amp;</type>
      <name>cooling_schedule_m</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>471512db453b2b2dfb680ee975fe7b5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>starting_temp_m</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>f1bf7960d590513c814605cf56b94213</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>current_temp_m</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>c8f3d267ac8558236187442c56f979bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>K_m</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>897dc5cbe59b9720cf16ab76c1b4bcfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::tr1::uniform_real</type>
      <name>ureal</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>bc473e5b126dc2df0e7d6638c5738e18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::tr1::mt19937</type>
      <name>rng</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>abe5b590aa0af758a9674b1b0e06752c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::tr1::variate_generator&lt; std::tr1::mt19937, std::tr1::uniform_real&lt; double &gt; &gt;</type>
      <name>gen</name>
      <anchorfile>a00022.html</anchorfile>
      <anchor>78073b6b0df58bf35339828c97a5eb76</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::exponential_cooling</name>
    <filename>a00007.html</filename>
    <base>mets::abstract_cooling_schedule</base>
    <member kind="function">
      <type></type>
      <name>exponential_cooling</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>2f893b0d4dc0f6a6fbbdbffc79aad3a0</anchor>
      <arglist>(double alpha=0.95)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator()</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>8411a48c3cbc35efdd248560738ccbaa</anchor>
      <arglist>(double temp, feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>factor_m</name>
      <anchorfile>a00007.html</anchorfile>
      <anchor>b20a86252f741b15812eeb9675cebc71</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::linear_cooling</name>
    <filename>a00010.html</filename>
    <base>mets::abstract_cooling_schedule</base>
    <member kind="function">
      <type></type>
      <name>linear_cooling</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>8f97edfd54f03301ecbd54ee74127ef0</anchor>
      <arglist>(double delta=0.1)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>operator()</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>3128acbc16f2034d61ee1bb86b9988a7</anchor>
      <arglist>(double temp, feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>decrement_m</name>
      <anchorfile>a00010.html</anchorfile>
      <anchor>27c9e2285cd6a283b17c526f9a787ab7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::aspiration_criteria_chain</name>
    <filename>a00003.html</filename>
    <member kind="function">
      <type></type>
      <name>aspiration_criteria_chain</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>4ac27009ba58181dc16fdeba7162418c</anchor>
      <arglist>(aspiration_criteria_chain *next=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>aspiration_criteria_chain</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>c3b408d6651e2437ed4ac138fe752d5a</anchor>
      <arglist>(const aspiration_criteria_chain &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>aspiration_criteria_chain &amp;</type>
      <name>operator=</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>72d6400eb21b3eb821892de5e5b0cd07</anchor>
      <arglist>(const aspiration_criteria_chain &amp;other)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~aspiration_criteria_chain</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>b7e8f2b3fad2faff0df4e137399db0e3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual bool</type>
      <name>operator()</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>a3417b0edf43e91424f697c9022a5092</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;as)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>aspiration_criteria_chain *</type>
      <name>next_m</name>
      <anchorfile>a00003.html</anchorfile>
      <anchor>c2217cbf77ea17030d1f3bafe54f8a27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::tabu_list_chain</name>
    <filename>a00024.html</filename>
    <member kind="function">
      <type></type>
      <name>tabu_list_chain</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>26e7c52ab636e9a84b95d48ee7f8a6a1</anchor>
      <arglist>(const tabu_list_chain &amp;)</arglist>
    </member>
    <member kind="function">
      <type>tabu_list_chain &amp;</type>
      <name>operator=</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>7347fdbe887194d970b0189531b8bf4e</anchor>
      <arglist>(const tabu_list_chain &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tabu_list_chain</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>58a0088e572ec5b923339f2d34bd53b6</anchor>
      <arglist>(unsigned int tenure)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tabu_list_chain</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>09efc3cb9bca2efb792c05a2e97d5930</anchor>
      <arglist>(tabu_list_chain *next, unsigned int tenure)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~tabu_list_chain</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>0b0751c6d11f1c219a04ddd7cbd64089</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>tabu</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>6ea0ee33b016bb9ea0dadcd225994a30</anchor>
      <arglist>(feasible_solution &amp;sol, move &amp;mov)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool</type>
      <name>is_tabu</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>b4e1bd820e1a6118112d565b079bb0e5</anchor>
      <arglist>(feasible_solution &amp;sol, move &amp;mov)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>tenure</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>a86d0be85bfeae0948dc98a0801fde6b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int</type>
      <name>tenure</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>98eb328229220535d19a4b7e088f1c5a</anchor>
      <arglist>(unsigned int tenure)=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>tabu_list_chain *</type>
      <name>next_m</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>67c5bfda6008cd463f4beac58e6e32d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned int</type>
      <name>tenure_m</name>
      <anchorfile>a00024.html</anchorfile>
      <anchor>e0bd990b1bcdcc1ffb0193183eb8ff0b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::tabu_search</name>
    <filename>a00025.html</filename>
    <base>mets::abstract_search</base>
    <member kind="function">
      <type></type>
      <name>tabu_search</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>3c8b82c967e717d343a4c5a80a15c6b9</anchor>
      <arglist>(feasible_solution &amp;starting_solution, feasible_solution &amp;best_sol, move_manager &amp;move_manager_inst, tabu_list_chain &amp;tabus, aspiration_criteria_chain &amp;aspiration, termination_criteria_chain &amp;termination)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>tabu_search</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>e055de4f0e9e319f5924848834c35004</anchor>
      <arglist>(const tabu_search &amp;)</arglist>
    </member>
    <member kind="function">
      <type>tabu_search &amp;</type>
      <name>operator=</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>5c546eb33de16fbad559fbc2e9399458</anchor>
      <arglist>(const tabu_search &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>search</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>dd4ca76f7cf3529762c43d6384440f8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>step</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>980c359007f4ffc5c6eca62bdffeca20</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const tabu_list_chain &amp;</type>
      <name>get_tabu_list</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>d0f53ec514ba3a85866cd569c6cdf3a1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const aspiration_criteria_chain &amp;</type>
      <name>get_aspiration_criteria</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>d955f8cd399213b270ecd25ee7efeb44</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const termination_criteria_chain &amp;</type>
      <name>get_termination_criteria</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>0229452828a9c215a30b58c85c9aa4f6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>ASPIRATION_CRITERIA_MET</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>e4c389b2e57e6b10bfefabfa2a4ff222</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>tabu_list_chain &amp;</type>
      <name>tabu_list_m</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>9f6eebc2b6136869a7853c6b4ed9e3c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>aspiration_criteria_chain &amp;</type>
      <name>aspiration_criteria_m</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>6da437aa5d9a3bcccdb99469aad1a63f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>termination_criteria_chain &amp;</type>
      <name>termination_criteria_m</name>
      <anchorfile>a00025.html</anchorfile>
      <anchor>583b040bca671f3727d4a011eb39eb24</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::simple_tabu_list</name>
    <filename>a00021.html</filename>
    <base>mets::tabu_list_chain</base>
    <member kind="typedef">
      <type>std::deque&lt; move * &gt;::const_iterator</type>
      <name>const_iterator</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>aa58be0929511f2c2ed84d765932da47</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::deque&lt; move * &gt;::size_type</type>
      <name>size_type</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>54dedee49a79f96601770c100ae9a023</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_tabu_list</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>cf40a93816b812b909d8c091eb5babdd</anchor>
      <arglist>(unsigned int tenure)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>simple_tabu_list</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>5d25561c383c65355e2f9aa8a45932f9</anchor>
      <arglist>(tabu_list_chain *next, unsigned int tenure)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~simple_tabu_list</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>d8c203aa601bf363f0037c60c6bc5c3c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>begin</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>74ddc78371c8ea36ebe66ef19534dcd4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const_iterator</type>
      <name>end</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>8fdd0804fdd3547237ec41c070f1d12f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tabu</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>c5a5ba0389d4e09042eb4efdf3266639</anchor>
      <arglist>(feasible_solution &amp;sol, move &amp;mov)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>is_tabu</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>c43dfd2c412f5fe075ccee91c6c650ff</anchor>
      <arglist>(feasible_solution &amp;sol, move &amp;mov)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned int</type>
      <name>tenure</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>fd3757c2edd65af4dd6487d5678af130</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>tenure</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>872d78db0996852105355138cee7b5f0</anchor>
      <arglist>(unsigned int tenure_value)</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::deque&lt; move * &gt;</type>
      <name>move_list_type</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>e6a7eba6924e9fbd7e7b056f4c26ea89</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::tr1::unordered_map&lt; mana_move *, int, mana_move_hash, dereferenced_equal_to&lt; mana_move * &gt; &gt;</type>
      <name>move_map_type</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>0f732d6a1607f4391d1b461e366fc1a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>move_list_type</type>
      <name>tabu_moves_m</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>60a35ec6f3207da45b33b2513a974a36</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>move_map_type</type>
      <name>tabu_hash_m</name>
      <anchorfile>a00021.html</anchorfile>
      <anchor>dde59ad7324bdbe9a8bf3304144eb094</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::best_ever_criteria</name>
    <filename>a00004.html</filename>
    <base>mets::aspiration_criteria_chain</base>
    <member kind="function">
      <type></type>
      <name>best_ever_criteria</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>4f249c5a80b385d31aa95c3f3e4cd480</anchor>
      <arglist>(aspiration_criteria_chain *next)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00004.html</anchorfile>
      <anchor>9ab3b6c3a7e70fccb495add4635230e9</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::iteration_termination_criteria</name>
    <filename>a00009.html</filename>
    <base>mets::termination_criteria_chain</base>
    <member kind="function">
      <type></type>
      <name>iteration_termination_criteria</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>1e3bdc8f993b0c6a46db54802ec32b1f</anchor>
      <arglist>(int max)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>iteration_termination_criteria</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a6184032fcb4d552d13b1f2a4f92cbb0</anchor>
      <arglist>(termination_criteria_chain *next, int max)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>b4554d2760b6e50c0102618290a148a7</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>5527220ab4b7c669f0c1cdec1f8dc0b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>max_m</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>a616d1fe17f9b7eba4befeb2d094e996</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>iterations_m</name>
      <anchorfile>a00009.html</anchorfile>
      <anchor>582c374d42c008a2b752c21412066572</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::noimprove_termination_criteria</name>
    <filename>a00017.html</filename>
    <base>mets::termination_criteria_chain</base>
    <member kind="function">
      <type></type>
      <name>noimprove_termination_criteria</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>72cc3797e0adbc7a220f2cfe0a5fd902</anchor>
      <arglist>(int max)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>noimprove_termination_criteria</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>15b3cebd920a6cac39184271ee0643fc</anchor>
      <arglist>(termination_criteria_chain *next, int max)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>964ad11c4feb8298024f69d15e12dc90</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>e2290dc84c96cbbef4b54919b989b4c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>gol_type</type>
      <name>best_cost_m</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>722210c52c463b7b640d3c9b9a933075</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>max_noimprove_m</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>34bf5314f498cd845336e417a294ea5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>iterations_left_m</name>
      <anchorfile>a00017.html</anchorfile>
      <anchor>8e57e33433f306d4a6ff654f6fb0cf6a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::threshold_termination_criteria</name>
    <filename>a00027.html</filename>
    <base>mets::termination_criteria_chain</base>
    <member kind="function">
      <type></type>
      <name>threshold_termination_criteria</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>680a8b4381c9c4b1193b08705b477245</anchor>
      <arglist>(gol_type level)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>threshold_termination_criteria</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>48bba59eb18d017a5b2fca8ec57a7409</anchor>
      <arglist>(termination_criteria_chain *next, gol_type level)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator()</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>3a6237ad9d00fe3fdb424bcb7bb81213</anchor>
      <arglist>(feasible_solution &amp;fs, abstract_search &amp;ts)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>reset</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>5516a6a9c634a7ee18578a794ff9b784</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>gol_type</type>
      <name>level_m</name>
      <anchorfile>a00027.html</anchorfile>
      <anchor>bb3ef57c300a3ad009bf39a1340b9584</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::update_observer</name>
    <filename>a00028.html</filename>
    <templarg>observed_subject</templarg>
    <member kind="function">
      <type></type>
      <name>update_observer</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>0f20603c0e9d109d2b8b26a4391ef588</anchor>
      <arglist>(observed_subject *who)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>a00028.html</anchorfile>
      <anchor>ce0cfbc6604dbad39b7557bca3a2b9e1</anchor>
      <arglist>(observer&lt; observed_subject &gt; *o)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::subject</name>
    <filename>a00023.html</filename>
    <templarg>observed_subject</templarg>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>attach</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>580c481db07f883261c0a24f0f201067</anchor>
      <arglist>(observer&lt; observed_subject &gt; &amp;o)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>detach</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>f6b5055d74cb5671e46bb57a4109cf3a</anchor>
      <arglist>(observer&lt; observed_subject &gt; &amp;o)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>notify</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>604a3c6cb19a470779170e29528f3e83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>set&lt; observer&lt; observed_subject &gt; * &gt;</type>
      <name>observers_m</name>
      <anchorfile>a00023.html</anchorfile>
      <anchor>018e084d1ca0f43f09d2cb46219a32c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>mets::observer</name>
    <filename>a00018.html</filename>
    <templarg>observed_subject</templarg>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>update</name>
      <anchorfile>a00018.html</anchorfile>
      <anchor>059bb913e90c74ccc4a18d92919bb331</anchor>
      <arglist>(observed_subject *)=0</arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>metslib/</name>
    <path>/home/mirko/dev/metslib-coin/releases/0.4.3/metslib/</path>
    <filename>dir_f5759a71700e767f575117cac5281f76.html</filename>
    <file>config.h</file>
    <file>mets.h</file>
    <file>metslib_config.h</file>
    <file>observer.h</file>
  </compound>
</tagfile>
