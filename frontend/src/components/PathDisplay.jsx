import React from 'react';
import { Box, Typography, List, ListItem, ListItemText, Divider, Chip, Alert } from '@mui/material';

const PathDisplay = ({ results, sport, showBoth }) => {
  const renderConnection = (reason) => {
    if (!reason) return '';
    if (reason.includes('team')) return '🏟️ Team';
    if (reason.includes('goals')) return '🥅 Goals';
    if (reason.includes('yellow')) return '⚠️ Discipline';
    if (reason.includes('games')) return '👟 Appearances';
    if (reason.includes('points')) return '🏅 Points';
    if (reason.includes('rebounds')) return '✋ Rebounds';
    if (reason.includes('assists')) return '🎯 Assists';
    return '🔗 Connection';
  };

  const renderPath = (path, algorithm) => {
    if (!Array.isArray(path)) {
      return (
        <Alert severity="info" sx={{ mt: 2 }}>
          No path found using {algorithm}
        </Alert>
      );
    }

    return (
      <Box sx={{ mb: 4 }}>
        <Typography variant="h5" gutterBottom>
          {algorithm} Path ({results[`${algorithm}Time`]}s)
        </Typography>
        <List dense sx={{ bgcolor: 'background.paper' }}>
          {path.map(([player, reason], index) => (
            <React.Fragment key={index}>
              <ListItem alignItems="flex-start">
                <ListItemText
                  primary={player?.name || 'Unknown player'}
                  secondary={
                    index < path.length - 1 && (
                      <Box sx={{ display: 'flex', alignItems: 'center', mt: 1 }}>
                        <Chip
                          label={renderConnection(reason)}
                          size="small"
                          sx={{ mr: 1 }}
                        />
                        <Typography variant="body2" component="span">
                          {reason}
                        </Typography>
                      </Box>
                    )
                  }
                />
              </ListItem>
              {index < path.length - 1 && <Divider component="li" />}
            </React.Fragment>
          ))}
        </List>
      </Box>
    );
  };

  const bfsPath = results?.bfsPath || [];
  const dijkPath = results?.dijkPath || [];

  return (
    <Box>
      {showBoth ? (
        <>
          {renderPath(bfsPath, 'BFS')}
          {renderPath(dijkPath, 'Dijkstra')}
        </>
      ) : (
        renderPath(
          results.bfsTime < results.dijkTime ? bfsPath : dijkPath,
          results.bfsTime < results.dijkTime ? 'BFS' : 'Dijkstra'
        )
      )}
    </Box>
  );
};

export default PathDisplay;