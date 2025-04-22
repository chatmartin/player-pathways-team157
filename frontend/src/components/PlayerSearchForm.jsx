//PlayerSearchForm.jsx
import React from 'react';
import { Autocomplete, TextField, Button, Grid, CircularProgress } from '@mui/material';

const PlayerSearchForm = ({ sport, players, selectedPlayers, onSelect, onSearch, loading }) => {
  const getPlayerLabel = (player) => {
    if (!player || typeof player !== 'object') return '';
    const details = [];
  
    if (sport === 'basketball') {
      details.push(`🏀 ${player.points ?? 0} pts`);
      details.push(`⏳ ${player.teamTime?.length || 0} seasons`);
    } else {
      details.push(`⚽ ${player.goals ?? 0} goals`);
      details.push(`🟨 ${player.yellow ?? 0} yellows`);
    }
  
    return `${player.name ?? 'Unknown'} (${details.join(', ')})`;
  };

  return (
    <Grid 
      container 
      spacing={2}
      justifyContent="center"
      sx={{ 
        mb: 4,
        width: '100%'
      }}
    >
      <Grid item xs={12} md={8} lg={5}>
        <Autocomplete
          options={players}
          loading={players.length === 0}
          getOptionLabel={getPlayerLabel}
          isOptionEqualToValue={(option, value) => option.name === value.name}
          value={selectedPlayers.from}
          onChange={(_, value) => onSelect(value, 'from')}
          renderInput={(params) => (
            <TextField
              {...params}
              label="Select Player A"
              variant="outlined"
              fullWidth
              InputProps={{
                ...params.InputProps,
                endAdornment: (
                  <>
                    {players.length === 0 && !loading ? (
                      <CircularProgress color="inherit" size={20} />
                    ) : null}
                    {params.InputProps.endAdornment}
                  </>
                ),
              }}
            />
          )}
          disabled={loading}
        />
      </Grid>

      <Grid item xs={12} md={8} lg={5}>
        <Autocomplete
          options={players}
          loading={players.length === 0}
          getOptionLabel={getPlayerLabel}
          isOptionEqualToValue={(option, value) => option.name === value.name}
          value={selectedPlayers.to}
          onChange={(_, value) => onSelect(value, 'to')}
          renderInput={(params) => (
            <TextField
              {...params}
              label="Select Player B"
              variant="outlined"
              fullWidth
              InputProps={{
                ...params.InputProps,
                endAdornment: (
                  <>
                    {players.length === 0 && !loading ? (
                      <CircularProgress color="inherit" size={20} />
                    ) : null}
                    {params.InputProps.endAdornment}
                  </>
                ),
              }}
            />
          )}
          disabled={loading}
        />
      </Grid>

      <Grid 
        item 
        xs={12} 
        md={8} 
        lg={2} 
        sx={{ 
          display: 'flex', 
          justifyContent: 'center',
          alignItems: 'center' 
        }}
      >
        <Button
          variant="contained"
          size="large"
          onClick={onSearch}
          disabled={loading || !selectedPlayers.from || !selectedPlayers.to}
          sx={{ height: '56px', width: '100%', maxWidth: '200px' }}
        >
          {loading ? <CircularProgress size={24} color="inherit" /> : 'Find Path'}
        </Button>
      </Grid>
    </Grid>
  );
};

export default PlayerSearchForm;