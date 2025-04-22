import React from "react";
import {
  Box,
  Typography,
  Chip,
  Stepper,
  Step,
  StepLabel,
  Alert,
  Tooltip     //  ← NEW
} from "@mui/material";

/* ------------------------------------------------------------------ */
/* helper to translate edge “reason” into an icon / short label       */
const iconFor = (reason = "") => {
  if (reason.includes("team"))     return "🏟️";
  if (reason.includes("goals"))    return "🥅";
  if (reason.includes("yellow"))   return "⚠️";
  if (reason.includes("games"))    return "👟";
  if (reason.includes("points"))   return "🏅";
  if (reason.includes("rebounds")) return "✋";
  if (reason.includes("assists"))  return "🎯";
  return "🔗";
};

/* ------------------------------------------------------------------ */
/* reusable visual block (single algorithm)                           */
function PathBlock({ path, algorithm, time }) {
  /* empty / no path */
  if (!Array.isArray(path) || !path.length) {
    return (
      <Alert severity="info" sx={{ mt: 2 }}>
        No path found using {algorithm}
      </Alert>
    );
  }

  /* horizontal for ≤ 7 hops, vertical otherwise */
  const orientation = path.length > 7 ? "vertical" : "horizontal";

  return (
    <Box sx={{ mb: 6 }}>
      <Typography variant="h5" gutterBottom sx={{ mb: 2 /* extra space */ }}>
        {algorithm} Path&nbsp;
        <Chip label={`${time}s`} size="small" color="primary" />
      </Typography>

      <Stepper
        orientation={orientation}
        alternativeLabel={orientation === "horizontal"}
        sx={
          orientation === "horizontal"
            ? { mt: 4, overflowX: "auto", pb: 2 }  // space above + scroll if long
            : { mt: 1 }
        }
      >
        {path.map(([player, reason], idx) => (
          <Step key={idx} completed>
            <StepLabel
              optional={
                idx < path.length - 1 && reason ? (
                  /* -------------------  TOOLTIP HERE  ------------------- */
                  <Tooltip title={reason} arrow placement="top">
                    <Chip label={iconFor(reason)} size="small" />
                  </Tooltip>
                ) : null
              }
            >
              {player?.name ?? "Unknown"}
            </StepLabel>
          </Step>
        ))}
      </Stepper>
    </Box>
  );
}

/* ------------------------------------------------------------------ */
/* exported wrapper: decides which path(s) to render                   */
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
          <PathBlock path={bfsPath} algorithm="BFS"      time={bfsTime} />
          <PathBlock path={djkPath} algorithm="Dijkstra" time={djkTime} />
        </>
      ) : fasterIsBfs ? (
        <PathBlock path={bfsPath} algorithm="BFS" time={bfsTime} />
      ) : (
        <PathBlock path={djkPath} algorithm="Dijkstra" time={djkTime} />
      )}
    </Box>
  );
};

export default PathDisplay;
