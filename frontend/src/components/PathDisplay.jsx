// PathDisplay.jsx
import React from 'react';
import {
  Box,
  Typography,
  Chip,
  Stepper,
  Step,
  StepLabel,
  Alert,
} from '@mui/material';
import ForceGraph2D from 'react-force-graph-2d'; 

/* ------------------------------------------------------------------ */
/* helper to translate edge “reason” into an icon / short label       */
const iconFor = (reason = '') => {
  if (reason.includes('team'))     return '🏟️';
  if (reason.includes('goals'))    return '🥅';
  if (reason.includes('yellow'))   return '⚠️';
  if (reason.includes('games'))    return '👟';
  if (reason.includes('points'))   return '🏅';
  if (reason.includes('rebounds')) return '✋';
  if (reason.includes('assists'))  return '🎯';
  return '🔗';
};

/* ------------ helper: path  → nodes / links for the graph -------------- */
const graphFromPath = (path = []) => {
    const nodes = path.map(([p]) => ({ id: p.name }));
    const links = path.slice(1).map(([, r], i) => ({
      source: path[i][0].name,
      target: path[i + 1][0].name,
      label : r,
    }));
    return { nodes, links };
  };
  
  /* ------------ reusable visual block  (stepper + graph) ----------------- */
  function PathBlock({ path, algorithm, time }) {
    /* empty / no path */
    if (!Array.isArray(path) || !path.length) {
      return (
        <Alert severity="info" sx={{ mt: 2 }}>
          No path found using {algorithm}
        </Alert>
      );
    }
  
    const orientation = path.length > 7 ? 'vertical' : 'horizontal';
    const graphData  = graphFromPath(path);
  
    return (
      <Box sx={{ mb: 6 }}>
        {/* title */}
        <Typography variant="h5" gutterBottom>
          {algorithm} Path&nbsp;
          <Chip label={`${time}s`} size="small" color="primary" />
        </Typography>
  
        {/* stepper */}
        <Stepper
          orientation={orientation}
          alternativeLabel={orientation === 'horizontal'}
          sx={orientation === 'horizontal' ? { overflowX: 'auto', pb: 2 } : {}}
        >
          {path.map(([player, reason], idx) => (
            <Step key={idx} completed>
              <StepLabel
                optional={
                  idx < path.length - 1 && reason ? (
                    <Chip label={iconFor(reason)} size="small" />
                  ) : null
                }
              >
                {player.name}
              </StepLabel>
            </Step>
          ))}
        </Stepper>
  
        {/* force‑directed graph */}
        <ForceGraph2D
          graphData={graphData}
          nodeLabel="id"
          width={800}
          height={400}
          linkDirectionalArrowLength={4}
          linkDirectionalArrowRelPos={1}
          nodeCanvasObjectMode={() => 'after'}  // draw labels
          nodeCanvasObject={(node, ctx) => {
            ctx.fillStyle = '#000';
            ctx.font      = '10px sans-serif';
            ctx.fillText(node.id, node.x + 6, node.y + 2);
          }}
        />
      </Box>
    );
  }
  
  /* ------------ wrapper originally exported from this file --------------- */
  const PathDisplay = ({ results, showBoth }) => {
    const bfsPath  = results?.bfsPath  || [];
    const djkPath  = results?.dijkPath || [];
    const bfsTime  = results?.bfsTime  ?? 0;
    const djkTime  = results?.dijkTime ?? 0;
    const fasterIsBfs = bfsTime < djkTime;
  
    return (
      <Box>
        {showBoth ? (
          <>
            <PathBlock path={bfsPath}  algorithm="BFS"      time={bfsTime} />
            <PathBlock path={djkPath}  algorithm="Dijkstra" time={djkTime} />
          </>
        ) : fasterIsBfs ? (
          <PathBlock path={bfsPath}  algorithm="BFS"      time={bfsTime} />
        ) : (
          <PathBlock path={djkPath}  algorithm="Dijkstra" time={djkTime} />
        )}
      </Box>
    );
  };
  
  export default PathDisplay;