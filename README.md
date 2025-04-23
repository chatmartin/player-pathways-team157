<h1>Project Overview</h1>

<p>This project implements a C++ backend using the Crow framework to support queries on a dynamic graph built from soccer and basketball data relationships. The frontend, written in React, lets users explore connection paths between soccer or basketball players. BFS and Dijkstra algorithms are implemented to find the shortest path between any two players.</p>

<h2>Getting Started</h2>

<h3>Technologies Used</h3>
<ul>
  <li>C++ (Crow HTTP server)</li>
  <li>React.js</li>
  <li>CSV as data source</li>
</ul>

<h3>Installation Instructions</h3>
<ol>
  <li>Clone the repository:</li>
</ol>

<pre><code>git clone https://github.com/chatmartin/player-pathways-team157.git</code></pre>

<ol start="2">
  <li>Build the C++ backend</li>
</ol>

<pre><code>cd player-pathways-team157
mkdir build && cd build
cmake ..
make
</code></pre>

<ol start="3">
  <li>Run the backend server:</li>
</ol>
<pre><code>./main</code></pre>

<ol start="4">
  <li>Navigate to the frontend folder and start React:</li>
</ol>
<pre><code>cd frontend
npm install
npm install axios
npm install @mui/material @emotion/react @emotion/styled
npm start
</code></pre>

<h2>Running the Backend</h2>

<p>The C++ backend reads CSV files and builds a graph of player-team relationships.</p>

<p><strong>Endpoints:</strong></p>
<ul>
  <li><code>/fball_graph</code> — returns node-link JSON graph for soccer</li>
  <li><code>/bball_graph</code> — returns node-link JSON graph for basketball</li>
  <li><code>/fballAlgo</code> — POST body with source, target, algo="bfs" or "dijkstra"</li>
  <li><code>/bballAlgo</code> — same but for basketball</li>
</ul>

<h2>Running the Frontend</h2>

<p>The frontend renders the graph and makes POST requests to the backend to fetch paths. Players can be selected via dropdown and paths are visualized interactively.</p>

<h2>Team Workflow</h2>

<h3>Branches</h3>
<ul>
  <li><code>main</code> — Final project state</li>
  <li><code>frontend-feature</code> — React UI</li>
  <li><code>player-class</code> — Player graph modeling</li>
</ul>

<h2>Resources</h2>
<ul>
  <li><a href="https://github.com/CrowCpp/Crow">Crow Framework</a></li>
  <li><a href="https://reactjs.org">React Docs</a></li>
  <li><a href="https://github.com/chriskohlhoff/asio/releases/tag/asio-1-18-2">Asio Library</a></li>
</ul>
