<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN"
   "http://www.w3.org/TR/html4/strict.dtd">

<html>
<head>
  <title></title>
  <meta http-equiv="content-type" content="text/html; charset=latin-1">
  <style type="text/css">
td.linenos { background-color: #f0f0f0; padding-right: 10px; }
span.lineno { background-color: #f0f0f0; padding: 0 5px 0 5px; }
pre { line-height: 125%; }
body .hll { background-color: #ffffcc }
body  { background: #ffffff; }
body .c { color: #008800; font-style: italic } /* Comment */
body .err { color: #a61717; background-color: #e3d2d2 } /* Error */
body .k { color: #000080; font-weight: bold } /* Keyword */
body .cm { color: #008800; font-style: italic } /* Comment.Multiline */
body .cp { color: #008080 } /* Comment.Preproc */
body .c1 { color: #008800; font-style: italic } /* Comment.Single */
body .cs { color: #008800; font-weight: bold } /* Comment.Special */
body .gd { color: #000000; background-color: #ffdddd } /* Generic.Deleted */
body .ge { font-style: italic } /* Generic.Emph */
body .gr { color: #aa0000 } /* Generic.Error */
body .gh { color: #999999 } /* Generic.Heading */
body .gi { color: #000000; background-color: #ddffdd } /* Generic.Inserted */
body .go { color: #888888 } /* Generic.Output */
body .gp { color: #555555 } /* Generic.Prompt */
body .gs { font-weight: bold } /* Generic.Strong */
body .gu { color: #aaaaaa } /* Generic.Subheading */
body .gt { color: #aa0000 } /* Generic.Traceback */
body .kc { color: #000080; font-weight: bold } /* Keyword.Constant */
body .kd { color: #000080; font-weight: bold } /* Keyword.Declaration */
body .kn { color: #000080; font-weight: bold } /* Keyword.Namespace */
body .kp { color: #000080; font-weight: bold } /* Keyword.Pseudo */
body .kr { color: #000080; font-weight: bold } /* Keyword.Reserved */
body .kt { color: #000080; font-weight: bold } /* Keyword.Type */
body .m { color: #0000FF } /* Literal.Number */
body .s { color: #0000FF } /* Literal.String */
body .na { color: #FF0000 } /* Name.Attribute */
body .nt { color: #000080; font-weight: bold } /* Name.Tag */
body .ow { font-weight: bold } /* Operator.Word */
body .w { color: #bbbbbb } /* Text.Whitespace */
body .mf { color: #0000FF } /* Literal.Number.Float */
body .mh { color: #0000FF } /* Literal.Number.Hex */
body .mi { color: #0000FF } /* Literal.Number.Integer */
body .mo { color: #0000FF } /* Literal.Number.Oct */
body .sb { color: #0000FF } /* Literal.String.Backtick */
body .sc { color: #800080 } /* Literal.String.Char */
body .sd { color: #0000FF } /* Literal.String.Doc */
body .s2 { color: #0000FF } /* Literal.String.Double */
body .se { color: #0000FF } /* Literal.String.Escape */
body .sh { color: #0000FF } /* Literal.String.Heredoc */
body .si { color: #0000FF } /* Literal.String.Interpol */
body .sx { color: #0000FF } /* Literal.String.Other */
body .sr { color: #0000FF } /* Literal.String.Regex */
body .s1 { color: #0000FF } /* Literal.String.Single */
body .ss { color: #0000FF } /* Literal.String.Symbol */
body .il { color: #0000FF } /* Literal.Number.Integer.Long */

  </style>
</head>
<body>
<h2></h2>

<div class="highlight"><pre><a name="n-1"></a><span class="lineno">  1</span> <span class="cm">/*</span>
<a name="n-2"></a><span class="lineno">  2</span> <span class="cm"> * Copyright (C) 2014  Tomasz Kramkowski &lt;tk@the-tk.com&gt;</span>
<a name="n-3"></a><span class="lineno">  3</span> <span class="cm"> *</span>
<a name="n-4"></a><span class="lineno">  4</span> <span class="cm"> * This program is free software. It is licensed under version 3 of the</span>
<a name="n-5"></a><span class="lineno">  5</span> <span class="cm"> * GNU General Public License.</span>
<a name="n-6"></a><span class="lineno">  6</span> <span class="cm"> *</span>
<a name="n-7"></a><span class="lineno">  7</span> <span class="cm"> * You should have received a copy of the GNU General Public License</span>
<a name="n-8"></a><span class="lineno">  8</span> <span class="cm"> * along with this program.  If not, see [http://www.gnu.org/licenses/].</span>
<a name="n-9"></a><span class="lineno">  9</span> <span class="cm"> */</span>
<a name="n-10"></a><span class="lineno"> 10</span> <span class="cp">#include &lt;stdbool.h&gt;</span>
<a name="n-11"></a><span class="lineno"> 11</span> <span class="cp">#include &lt;stdio.h&gt;</span>
<a name="n-12"></a><span class="lineno"> 12</span> <span class="cp">#include &lt;stdlib.h&gt;</span>
<a name="n-13"></a><span class="lineno"> 13</span> <span class="cp">#include &lt;time.h&gt;</span>
<a name="n-14"></a><span class="lineno"> 14</span> <span class="cp">#include &lt;xcb/xcb.h&gt;</span>
<a name="n-15"></a><span class="lineno"> 15</span> <span class="cp">#include &lt;xcb/xcb_image.h&gt;</span>
<a name="n-16"></a><span class="lineno"> 16</span> 
<a name="n-17"></a><span class="lineno"> 17</span> <span class="cp">#define BOARD_WIDTH 500</span>
<a name="n-18"></a><span class="lineno"> 18</span> <span class="cp">#define BOARD_HEIGHT 500</span>
<a name="n-19"></a><span class="lineno"> 19</span> 
<a name="n-20"></a><span class="lineno"> 20</span> <span class="cp">#define PIXEL 1</span>
<a name="n-21"></a><span class="lineno"> 21</span> 
<a name="n-22"></a><span class="lineno"> 22</span> <span class="cp">#define WIDTH (BOARD_WIDTH * PIXEL)</span>
<a name="n-23"></a><span class="lineno"> 23</span> <span class="cp">#define HEIGHT (BOARD_HEIGHT * PIXEL)</span>
<a name="n-24"></a><span class="lineno"> 24</span> 
<a name="n-25"></a><span class="lineno"> 25</span> <span class="cp">#define GOL_CLAMP(pos, max) ((pos) &lt; 0 ? (pos) + (max) : (pos) % (max))</span>
<a name="n-26"></a><span class="lineno"> 26</span> <span class="cp">#define GOL_CLAMPX(gol, pos) (GOL_CLAMP((pos), (gol)-&gt;width))</span>
<a name="n-27"></a><span class="lineno"> 27</span> <span class="cp">#define GOL_CLAMPY(gol, pos) (GOL_CLAMP((pos), (gol)-&gt;height))</span>
<a name="n-28"></a><span class="lineno"> 28</span> <span class="cp">#define GOL_RESOLVE_F(gol, x, y) ((gol)-&gt;buffers[(gol)-&gt;front][(GOL_CLAMPX(gol, x))\</span>
<a name="n-29"></a><span class="lineno"> 29</span> <span class="cp">		+ (GOL_CLAMPY(gol, y)) * (gol)-&gt;width])</span>
<a name="n-30"></a><span class="lineno"> 30</span> <span class="cp">#define GOL_RESOLVE_B(gol, x, y) ((gol)-&gt;buffers[!(gol)-&gt;front][(GOL_CLAMPX(gol, x))\</span>
<a name="n-31"></a><span class="lineno"> 31</span> <span class="cp">		+ (GOL_CLAMPY(gol, y)) * (gol)-&gt;width])</span>
<a name="n-32"></a><span class="lineno"> 32</span> 
<a name="n-33"></a><span class="lineno"> 33</span> <span class="k">typedef</span> <span class="k">struct</span> <span class="kt">gol_t</span> <span class="p">{</span>
<a name="n-34"></a><span class="lineno"> 34</span> 	<span class="kt">uint32_t</span> <span class="n">width</span><span class="p">,</span> <span class="n">height</span><span class="p">;</span>
<a name="n-35"></a><span class="lineno"> 35</span> 	<span class="kt">bool</span> <span class="o">*</span><span class="n">buffers</span><span class="p">[</span><span class="mi">2</span><span class="p">];</span>
<a name="n-36"></a><span class="lineno"> 36</span> 	<span class="kt">uint8_t</span> <span class="n">front</span><span class="p">;</span>
<a name="n-37"></a><span class="lineno"> 37</span> <span class="p">}</span> <span class="n">Gol</span><span class="p">;</span>
<a name="n-38"></a><span class="lineno"> 38</span> 
<a name="n-39"></a><span class="lineno"> 39</span> <span class="n">Gol</span> <span class="o">*</span><span class="nf">gol_new</span><span class="p">(</span><span class="kt">unsigned</span> <span class="k">const</span> <span class="kt">int</span> <span class="n">width</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="k">const</span> <span class="kt">int</span> <span class="n">height</span><span class="p">)</span>
<a name="n-40"></a><span class="lineno"> 40</span> <span class="p">{</span>
<a name="n-41"></a><span class="lineno"> 41</span> 	<span class="n">Gol</span> <span class="o">*</span><span class="n">gol</span> <span class="o">=</span> <span class="n">malloc</span><span class="p">(</span><span class="k">sizeof</span><span class="p">(</span><span class="n">Gol</span><span class="p">));</span>
<a name="n-42"></a><span class="lineno"> 42</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">width</span> <span class="o">=</span> <span class="n">width</span><span class="p">;</span>
<a name="n-43"></a><span class="lineno"> 43</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">height</span> <span class="o">=</span> <span class="n">height</span><span class="p">;</span>
<a name="n-44"></a><span class="lineno"> 44</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">front</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-45"></a><span class="lineno"> 45</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span> <span class="o">=</span> <span class="n">malloc</span><span class="p">(</span><span class="n">width</span> <span class="o">*</span> <span class="n">height</span> <span class="o">*</span> <span class="k">sizeof</span><span class="p">(</span><span class="kt">bool</span><span class="p">));</span>
<a name="n-46"></a><span class="lineno"> 46</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span> <span class="o">=</span> <span class="n">malloc</span><span class="p">(</span><span class="n">width</span> <span class="o">*</span> <span class="n">height</span> <span class="o">*</span> <span class="k">sizeof</span><span class="p">(</span><span class="kt">bool</span><span class="p">));</span>
<a name="n-47"></a><span class="lineno"> 47</span> 	<span class="k">return</span> <span class="n">gol</span><span class="p">;</span>
<a name="n-48"></a><span class="lineno"> 48</span> <span class="p">}</span>
<a name="n-49"></a><span class="lineno"> 49</span> 
<a name="n-50"></a><span class="lineno"> 50</span> <span class="kt">void</span> <span class="nf">gol_del</span><span class="p">(</span><span class="n">Gol</span> <span class="o">*</span><span class="n">gol</span><span class="p">)</span>
<a name="n-51"></a><span class="lineno"> 51</span> <span class="p">{</span>
<a name="n-52"></a><span class="lineno"> 52</span> 	<span class="n">free</span><span class="p">(</span><span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="mi">0</span><span class="p">]);</span>
<a name="n-53"></a><span class="lineno"> 53</span> 	<span class="n">free</span><span class="p">(</span><span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="mi">1</span><span class="p">]);</span>
<a name="n-54"></a><span class="lineno"> 54</span> 	<span class="n">free</span><span class="p">(</span><span class="n">gol</span><span class="p">);</span>
<a name="n-55"></a><span class="lineno"> 55</span> <span class="p">}</span>
<a name="n-56"></a><span class="lineno"> 56</span> 
<a name="n-57"></a><span class="lineno"> 57</span> <span class="kt">void</span> <span class="nf">gol_random</span><span class="p">(</span><span class="n">Gol</span> <span class="o">*</span><span class="k">const</span> <span class="n">gol</span><span class="p">,</span> <span class="kt">unsigned</span> <span class="k">const</span> <span class="kt">int</span> <span class="n">seed</span><span class="p">)</span>
<a name="n-58"></a><span class="lineno"> 58</span> <span class="p">{</span>
<a name="n-59"></a><span class="lineno"> 59</span> 	<span class="n">srand</span><span class="p">(</span><span class="n">seed</span><span class="p">);</span>
<a name="n-60"></a><span class="lineno"> 60</span> 	<span class="k">for</span> <span class="p">(</span><span class="kt">uint32_t</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">gol</span><span class="o">-&gt;</span><span class="n">width</span> <span class="o">*</span> <span class="n">gol</span><span class="o">-&gt;</span><span class="n">height</span><span class="p">;</span> <span class="n">i</span><span class="o">++</span><span class="p">)</span>
<a name="n-61"></a><span class="lineno"> 61</span> 		<span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="n">gol</span><span class="o">-&gt;</span><span class="n">front</span><span class="p">][</span><span class="n">i</span><span class="p">]</span> <span class="o">=</span> <span class="n">rand</span><span class="p">()</span> <span class="o">&lt;</span> <span class="mf">0.5</span> <span class="o">*</span> <span class="p">((</span><span class="kt">double</span><span class="p">)</span><span class="n">RAND_MAX</span> <span class="o">+</span> <span class="mf">1.0</span><span class="p">);</span>
<a name="n-62"></a><span class="lineno"> 62</span> <span class="p">}</span>
<a name="n-63"></a><span class="lineno"> 63</span> 
<a name="n-64"></a><span class="lineno"> 64</span> <span class="k">static</span> <span class="kt">uint32_t</span> <span class="nf">gol_clamp</span><span class="p">(</span><span class="k">const</span> <span class="kt">uint32_t</span> <span class="n">pos</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint32_t</span> <span class="n">max</span><span class="p">)</span> <span class="p">{</span>
<a name="n-65"></a><span class="lineno"> 65</span> 	<span class="k">return</span> <span class="n">pos</span> <span class="o">&lt;</span> <span class="mi">0</span> <span class="o">?</span> <span class="n">pos</span> <span class="o">+</span> <span class="n">max</span> <span class="o">:</span> <span class="n">pos</span> <span class="o">%</span> <span class="n">max</span><span class="p">;</span>
<a name="n-66"></a><span class="lineno"> 66</span> <span class="p">}</span>
<a name="n-67"></a><span class="lineno"> 67</span> 
<a name="n-68"></a><span class="lineno"> 68</span> <span class="k">static</span> <span class="kt">uint32_t</span> <span class="nf">gol_resolve_f</span><span class="p">(</span><span class="k">const</span> <span class="n">Gol</span> <span class="o">*</span><span class="k">const</span> <span class="n">gol</span><span class="p">,</span> 
<a name="n-69"></a><span class="lineno"> 69</span> 
<a name="n-70"></a><span class="lineno"> 70</span> <span class="k">static</span> <span class="kt">uint8_t</span> <span class="n">gol_neighbours</span><span class="p">(</span><span class="n">Gol</span> <span class="o">*</span><span class="k">const</span> <span class="n">gol</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint32_t</span> <span class="n">x</span><span class="p">,</span> <span class="k">const</span> <span class="kt">uint32_t</span> <span class="n">y</span><span class="p">)</span>
<a name="n-71"></a><span class="lineno"> 71</span> <span class="p">{</span>
<a name="n-72"></a><span class="lineno"> 72</span> 	<span class="kt">uint8_t</span> <span class="n">neighbours</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-73"></a><span class="lineno"> 73</span> 	<span class="k">for</span> <span class="p">(</span><span class="kt">int8_t</span> <span class="n">dx</span> <span class="o">=</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span> <span class="n">dx</span> <span class="o">&lt;=</span> <span class="mi">1</span><span class="p">;</span> <span class="n">dx</span><span class="o">++</span><span class="p">)</span>
<a name="n-74"></a><span class="lineno"> 74</span> 		<span class="k">for</span> <span class="p">(</span><span class="kt">int8_t</span> <span class="n">dy</span> <span class="o">=</span> <span class="o">-</span><span class="mi">1</span><span class="p">;</span> <span class="n">dy</span> <span class="o">&lt;=</span> <span class="mi">1</span><span class="p">;</span> <span class="n">dy</span><span class="o">++</span><span class="p">)</span>
<a name="n-75"></a><span class="lineno"> 75</span> 			<span class="k">if</span> <span class="p">(</span><span class="o">!</span><span class="p">(</span><span class="n">dx</span> <span class="o">==</span> <span class="mi">0</span> <span class="o">&amp;&amp;</span> <span class="n">dy</span> <span class="o">==</span> <span class="mi">0</span><span class="p">)</span> <span class="o">&amp;&amp;</span> <span class="n">GOL_RESOLVE_F</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span> <span class="o">+</span> <span class="n">dx</span><span class="p">,</span> <span class="n">y</span> <span class="o">+</span> <span class="n">dy</span><span class="p">))</span>
<a name="n-76"></a><span class="lineno"> 76</span> 				<span class="n">neighbours</span><span class="o">++</span><span class="p">;</span>
<a name="n-77"></a><span class="lineno"> 77</span> 	<span class="k">return</span> <span class="n">neighbours</span><span class="p">;</span>
<a name="n-78"></a><span class="lineno"> 78</span> <span class="p">}</span>
<a name="n-79"></a><span class="lineno"> 79</span> 
<a name="n-80"></a><span class="lineno"> 80</span> <span class="kt">void</span> <span class="nf">gol_simulate</span><span class="p">(</span><span class="n">Gol</span> <span class="o">*</span><span class="k">const</span> <span class="n">gol</span><span class="p">)</span>
<a name="n-81"></a><span class="lineno"> 81</span> <span class="p">{</span>
<a name="n-82"></a><span class="lineno"> 82</span> 	<span class="k">for</span> <span class="p">(</span><span class="kt">uint32_t</span> <span class="n">x</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">x</span> <span class="o">&lt;</span> <span class="n">gol</span><span class="o">-&gt;</span><span class="n">width</span><span class="p">;</span> <span class="n">x</span><span class="o">++</span><span class="p">)</span>
<a name="n-83"></a><span class="lineno"> 83</span> 		<span class="k">for</span> <span class="p">(</span><span class="kt">uint32_t</span> <span class="n">y</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">y</span> <span class="o">&lt;</span> <span class="n">gol</span><span class="o">-&gt;</span><span class="n">height</span><span class="p">;</span> <span class="n">y</span><span class="o">++</span><span class="p">)</span> <span class="p">{</span>
<a name="n-84"></a><span class="lineno"> 84</span> 			<span class="kt">uint8_t</span> <span class="n">neighbours</span> <span class="o">=</span> <span class="n">gol_neighbours</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">);</span>
<a name="n-85"></a><span class="lineno"> 85</span> 			<span class="k">if</span> <span class="p">(</span><span class="n">GOL_RESOLVE_F</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)){</span>
<a name="n-86"></a><span class="lineno"> 86</span> 				<span class="k">if</span> <span class="p">(</span><span class="n">neighbours</span> <span class="o">&lt;</span> <span class="mi">2</span><span class="p">)</span>
<a name="n-87"></a><span class="lineno"> 87</span> 					<span class="n">GOL_RESOLVE_B</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-88"></a><span class="lineno"> 88</span> 				<span class="k">else</span> <span class="k">if</span> <span class="p">(</span><span class="n">neighbours</span> <span class="o">&lt;=</span> <span class="mi">3</span><span class="p">)</span>
<a name="n-89"></a><span class="lineno"> 89</span> 					<span class="n">GOL_RESOLVE_B</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span>
<a name="n-90"></a><span class="lineno"> 90</span> 				<span class="k">else</span>
<a name="n-91"></a><span class="lineno"> 91</span> 					<span class="n">GOL_RESOLVE_B</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-92"></a><span class="lineno"> 92</span> 			<span class="p">}</span> <span class="k">else</span> <span class="p">{</span>
<a name="n-93"></a><span class="lineno"> 93</span> 				<span class="k">if</span> <span class="p">(</span><span class="n">neighbours</span> <span class="o">==</span> <span class="mi">3</span><span class="p">)</span>
<a name="n-94"></a><span class="lineno"> 94</span> 					<span class="n">GOL_RESOLVE_B</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)</span> <span class="o">=</span> <span class="mi">1</span><span class="p">;</span>
<a name="n-95"></a><span class="lineno"> 95</span> 				<span class="k">else</span>
<a name="n-96"></a><span class="lineno"> 96</span> 					<span class="n">GOL_RESOLVE_B</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">)</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-97"></a><span class="lineno"> 97</span> 			<span class="p">}</span>
<a name="n-98"></a><span class="lineno"> 98</span> 		<span class="p">}</span>
<a name="n-99"></a><span class="lineno"> 99</span> 
<a name="n-100"></a><span class="lineno">100</span> 	<span class="n">gol</span><span class="o">-&gt;</span><span class="n">front</span> <span class="o">=</span> <span class="o">!</span><span class="n">gol</span><span class="o">-&gt;</span><span class="n">front</span><span class="p">;</span>
<a name="n-101"></a><span class="lineno">101</span> <span class="p">}</span>
<a name="n-102"></a><span class="lineno">102</span> 
<a name="n-103"></a><span class="lineno">103</span> <span class="kt">int</span> <span class="nf">main</span><span class="p">(</span><span class="kt">int</span> <span class="n">argc</span><span class="p">,</span> <span class="kt">char</span> <span class="o">**</span><span class="n">argv</span><span class="p">)</span>
<a name="n-104"></a><span class="lineno">104</span> <span class="p">{</span>
<a name="n-105"></a><span class="lineno">105</span> 	<span class="kt">xcb_connection_t</span> <span class="o">*</span><span class="n">connection</span> <span class="o">=</span> <span class="n">xcb_connect</span><span class="p">(</span><span class="nb">NULL</span><span class="p">,</span> <span class="nb">NULL</span><span class="p">);</span>
<a name="n-106"></a><span class="lineno">106</span> 
<a name="n-107"></a><span class="lineno">107</span> 	<span class="kt">xcb_screen_t</span> <span class="o">*</span><span class="n">screen</span> <span class="o">=</span> <span class="n">xcb_setup_roots_iterator</span><span class="p">(</span><span class="n">xcb_get_setup</span><span class="p">(</span><span class="n">connection</span><span class="p">)).</span><span class="n">data</span><span class="p">;</span>
<a name="n-108"></a><span class="lineno">108</span> 
<a name="n-109"></a><span class="lineno">109</span> 	<span class="kt">uint32_t</span> <span class="n">mask</span> <span class="o">=</span> <span class="n">XCB_CW_BACK_PIXEL</span><span class="p">;</span>
<a name="n-110"></a><span class="lineno">110</span> 	<span class="kt">uint32_t</span> <span class="n">values</span><span class="p">[]</span> <span class="o">=</span> <span class="p">{</span><span class="n">screen</span><span class="o">-&gt;</span><span class="n">black_pixel</span><span class="p">};</span>
<a name="n-111"></a><span class="lineno">111</span> 
<a name="n-112"></a><span class="lineno">112</span> 	<span class="kt">xcb_drawable_t</span> <span class="n">window</span> <span class="o">=</span> <span class="n">xcb_generate_id</span><span class="p">(</span><span class="n">connection</span><span class="p">);</span>
<a name="n-113"></a><span class="lineno">113</span> 	<span class="n">xcb_create_window</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span>
<a name="n-114"></a><span class="lineno">114</span> 			<span class="mi">24</span><span class="p">,</span>
<a name="n-115"></a><span class="lineno">115</span> 			<span class="n">window</span><span class="p">,</span>
<a name="n-116"></a><span class="lineno">116</span> 			<span class="n">screen</span><span class="o">-&gt;</span><span class="n">root</span><span class="p">,</span>
<a name="n-117"></a><span class="lineno">117</span> 			<span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span>
<a name="n-118"></a><span class="lineno">118</span> 			<span class="n">WIDTH</span><span class="p">,</span> <span class="n">HEIGHT</span><span class="p">,</span>
<a name="n-119"></a><span class="lineno">119</span> 			<span class="mi">1</span><span class="p">,</span>
<a name="n-120"></a><span class="lineno">120</span> 			<span class="n">XCB_WINDOW_CLASS_INPUT_OUTPUT</span><span class="p">,</span>
<a name="n-121"></a><span class="lineno">121</span> 			<span class="n">screen</span><span class="o">-&gt;</span><span class="n">root_visual</span><span class="p">,</span>
<a name="n-122"></a><span class="lineno">122</span> 			<span class="n">mask</span><span class="p">,</span> <span class="n">values</span><span class="p">);</span>
<a name="n-123"></a><span class="lineno">123</span> 
<a name="n-124"></a><span class="lineno">124</span> 	<span class="kt">xcb_pixmap_t</span> <span class="n">pixmap</span> <span class="o">=</span> <span class="n">xcb_generate_id</span><span class="p">(</span><span class="n">connection</span><span class="p">);</span>
<a name="n-125"></a><span class="lineno">125</span> 	<span class="n">xcb_create_pixmap</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span>
<a name="n-126"></a><span class="lineno">126</span> 			<span class="mi">24</span><span class="p">,</span>
<a name="n-127"></a><span class="lineno">127</span> 			<span class="n">pixmap</span><span class="p">,</span>
<a name="n-128"></a><span class="lineno">128</span> 			<span class="n">window</span><span class="p">,</span>
<a name="n-129"></a><span class="lineno">129</span> 			<span class="n">WIDTH</span><span class="p">,</span> <span class="n">HEIGHT</span><span class="p">);</span>
<a name="n-130"></a><span class="lineno">130</span> 
<a name="n-131"></a><span class="lineno">131</span> 	<span class="kt">uint8_t</span> <span class="o">*</span><span class="n">img</span> <span class="o">=</span> <span class="n">malloc</span><span class="p">(</span><span class="n">WIDTH</span> <span class="o">*</span> <span class="n">HEIGHT</span> <span class="o">*</span> <span class="mi">4</span><span class="p">);</span>
<a name="n-132"></a><span class="lineno">132</span> 	<span class="kt">xcb_image_t</span> <span class="o">*</span><span class="n">image</span> <span class="o">=</span> <span class="n">xcb_image_create</span><span class="p">(</span><span class="n">WIDTH</span><span class="p">,</span> <span class="n">HEIGHT</span><span class="p">,</span>
<a name="n-133"></a><span class="lineno">133</span> 			<span class="n">XCB_IMAGE_FORMAT_Z_PIXMAP</span><span class="p">,</span>
<a name="n-134"></a><span class="lineno">134</span> 			<span class="mi">8</span><span class="p">,</span> <span class="mi">24</span><span class="p">,</span> <span class="mi">32</span><span class="p">,</span>
<a name="n-135"></a><span class="lineno">135</span> 			<span class="mi">0</span><span class="p">,</span>
<a name="n-136"></a><span class="lineno">136</span> 			<span class="n">XCB_IMAGE_ORDER_MSB_FIRST</span><span class="p">,</span>
<a name="n-137"></a><span class="lineno">137</span> 			<span class="n">XCB_IMAGE_ORDER_LSB_FIRST</span><span class="p">,</span>
<a name="n-138"></a><span class="lineno">138</span> 			<span class="n">img</span><span class="p">,</span>
<a name="n-139"></a><span class="lineno">139</span> 			<span class="n">WIDTH</span> <span class="o">*</span> <span class="n">HEIGHT</span> <span class="o">*</span> <span class="mi">4</span><span class="p">,</span>
<a name="n-140"></a><span class="lineno">140</span> 			<span class="n">img</span><span class="p">);</span>
<a name="n-141"></a><span class="lineno">141</span> 
<a name="n-142"></a><span class="lineno">142</span> 	<span class="n">mask</span> <span class="o">=</span> <span class="n">XCB_GC_FOREGROUND</span> <span class="o">|</span> <span class="n">XCB_GC_BACKGROUND</span><span class="p">;</span>
<a name="n-143"></a><span class="lineno">143</span> 	<span class="n">values</span><span class="p">[</span><span class="mi">0</span><span class="p">]</span> <span class="o">=</span> <span class="n">screen</span><span class="o">-&gt;</span><span class="n">black_pixel</span><span class="p">;</span>
<a name="n-144"></a><span class="lineno">144</span> 	<span class="n">values</span><span class="p">[</span><span class="mi">1</span><span class="p">]</span> <span class="o">=</span> <span class="mh">0xFFFFFF</span><span class="p">;</span>
<a name="n-145"></a><span class="lineno">145</span> 
<a name="n-146"></a><span class="lineno">146</span> 	<span class="kt">xcb_gcontext_t</span> <span class="n">gc</span> <span class="o">=</span> <span class="n">xcb_generate_id</span><span class="p">(</span><span class="n">connection</span><span class="p">);</span>
<a name="n-147"></a><span class="lineno">147</span> 	<span class="n">xcb_create_gc</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span>
<a name="n-148"></a><span class="lineno">148</span> 			<span class="n">gc</span><span class="p">,</span>
<a name="n-149"></a><span class="lineno">149</span> 			<span class="n">pixmap</span><span class="p">,</span>
<a name="n-150"></a><span class="lineno">150</span> 			<span class="n">mask</span><span class="p">,</span> <span class="n">values</span><span class="p">);</span>
<a name="n-151"></a><span class="lineno">151</span> 
<a name="n-152"></a><span class="lineno">152</span> 	<span class="n">xcb_image_put</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span> <span class="n">pixmap</span><span class="p">,</span> <span class="n">gc</span><span class="p">,</span> <span class="n">image</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span>
<a name="n-153"></a><span class="lineno">153</span> 
<a name="n-154"></a><span class="lineno">154</span> 	<span class="n">xcb_map_window</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span> <span class="n">window</span><span class="p">);</span>
<a name="n-155"></a><span class="lineno">155</span> 	<span class="n">xcb_flush</span><span class="p">(</span><span class="n">connection</span><span class="p">);</span>
<a name="n-156"></a><span class="lineno">156</span> 
<a name="n-157"></a><span class="lineno">157</span> 	<span class="kt">uint8_t</span> <span class="n">value</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-158"></a><span class="lineno">158</span> 
<a name="n-159"></a><span class="lineno">159</span> 	<span class="kt">uint32_t</span> <span class="o">*</span><span class="n">limg</span><span class="p">;</span>
<a name="n-160"></a><span class="lineno">160</span> 
<a name="n-161"></a><span class="lineno">161</span> 	<span class="n">Gol</span> <span class="o">*</span><span class="n">gol</span> <span class="o">=</span> <span class="n">gol_new</span><span class="p">(</span><span class="n">BOARD_WIDTH</span><span class="p">,</span> <span class="n">BOARD_HEIGHT</span><span class="p">);</span>
<a name="n-162"></a><span class="lineno">162</span> 	<span class="n">gol_random</span><span class="p">(</span><span class="n">gol</span><span class="p">,</span> <span class="n">time</span><span class="p">(</span><span class="nb">NULL</span><span class="p">));</span>
<a name="n-163"></a><span class="lineno">163</span> 
<a name="n-164"></a><span class="lineno">164</span> 	<span class="k">while</span> <span class="p">(</span><span class="mi">1</span><span class="p">)</span> <span class="p">{</span>
<a name="n-165"></a><span class="lineno">165</span> 		<span class="n">limg</span> <span class="o">=</span> <span class="p">(</span><span class="kt">uint32_t</span> <span class="o">*</span><span class="p">)</span><span class="n">image</span><span class="o">-&gt;</span><span class="n">data</span><span class="p">;</span>
<a name="n-166"></a><span class="lineno">166</span> 
<a name="n-167"></a><span class="lineno">167</span> 		<span class="k">for</span> <span class="p">(</span><span class="kt">int</span> <span class="n">i</span> <span class="o">=</span> <span class="mi">0</span><span class="p">;</span> <span class="n">i</span> <span class="o">&lt;</span> <span class="n">BOARD_WIDTH</span> <span class="o">*</span> <span class="n">BOARD_HEIGHT</span><span class="p">;</span> <span class="n">i</span><span class="o">++</span><span class="p">)</span>
<a name="n-168"></a><span class="lineno">168</span> 			<span class="o">*</span><span class="p">(</span><span class="n">limg</span><span class="o">++</span><span class="p">)</span> <span class="o">=</span> <span class="n">gol</span><span class="o">-&gt;</span><span class="n">buffers</span><span class="p">[</span><span class="n">gol</span><span class="o">-&gt;</span><span class="n">front</span><span class="p">][</span><span class="n">i</span><span class="p">]</span> <span class="o">?</span> <span class="mh">0x00FFFF00</span> <span class="o">:</span> <span class="mh">0x00000000</span><span class="p">;</span>
<a name="n-169"></a><span class="lineno">169</span> 
<a name="n-170"></a><span class="lineno">170</span> 		<span class="n">xcb_image_put</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span> <span class="n">pixmap</span><span class="p">,</span> <span class="n">gc</span><span class="p">,</span> <span class="n">image</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">);</span>
<a name="n-171"></a><span class="lineno">171</span> 
<a name="n-172"></a><span class="lineno">172</span> 		<span class="n">xcb_copy_area</span><span class="p">(</span><span class="n">connection</span><span class="p">,</span>
<a name="n-173"></a><span class="lineno">173</span> 				<span class="n">pixmap</span><span class="p">,</span>
<a name="n-174"></a><span class="lineno">174</span> 				<span class="n">window</span><span class="p">,</span>
<a name="n-175"></a><span class="lineno">175</span> 				<span class="n">gc</span><span class="p">,</span>
<a name="n-176"></a><span class="lineno">176</span> 				<span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span>
<a name="n-177"></a><span class="lineno">177</span> 				<span class="mi">0</span><span class="p">,</span> <span class="mi">0</span><span class="p">,</span>
<a name="n-178"></a><span class="lineno">178</span> 				<span class="n">WIDTH</span><span class="p">,</span> <span class="n">HEIGHT</span><span class="p">);</span>
<a name="n-179"></a><span class="lineno">179</span> 		<span class="n">xcb_flush</span><span class="p">(</span><span class="n">connection</span><span class="p">);</span>
<a name="n-180"></a><span class="lineno">180</span> 		<span class="n">value</span><span class="o">++</span><span class="p">;</span>
<a name="n-181"></a><span class="lineno">181</span> 
<a name="n-182"></a><span class="lineno">182</span> 		<span class="n">gol_simulate</span><span class="p">(</span><span class="n">gol</span><span class="p">);</span>
<a name="n-183"></a><span class="lineno">183</span> 	<span class="p">}</span>
<a name="n-184"></a><span class="lineno">184</span> 	<span class="k">return</span> <span class="mi">0</span><span class="p">;</span>
<a name="n-185"></a><span class="lineno">185</span> <span class="p">}</span>
</pre></div>
</body>
</html>
