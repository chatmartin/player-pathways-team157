import React, { useState, useEffect } from 'react';
import axios from 'axios';
import {
  Container,
  Typography,
  Grid,
  FormControlLabel,
  Switch,
  CircularProgress,
  Alert,
  CssBaseline
} from '@mui/material';
import PlayerSearchForm from './components/PlayerSearchForm';
import PathDisplay from './components/PathDisplay';

const App = () => {
  const [sport, setSport] = useState('basketball');
  const [showBothAlgorithms, setShowBothAlgorithms] = useState(true);
  const [players, setPlayers] = useState([]);
  const [selectedPlayers, setSelectedPlayers] = useState({ from: null, to: null });
  const [results, setResults] = useState(null);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(false);

  useEffect(() => {
    const fetchPlayers = async () => {
      try {
        const endpoint = sport === 'basketball' ? '/bball_graph' : '/fball_graph';
        const response = await axios.get(`http://localhost:18080${endpoint}`);
        setPlayers(response.data.players || []);
        setError(null);
      } catch (err) {
        setError('Failed to fetch players. Please try again later.');
        setPlayers([]);
      }
    };
    
    fetchPlayers();
    setSelectedPlayers({ from: null, to: null });
    setResults(null);
  }, [sport]);

  const handleSearch = async () => {
    if (!selectedPlayers.from || !selectedPlayers.to) {
      setError('Please select both players');
      return;
    }

    setLoading(true);
    try {
      const endpoint = sport === 'basketball' ? '/bballAlgo' : '/fballAlgo';
      const response = await axios.post(`http://localhost:18080${endpoint}`, {
        from: selectedPlayers.from.name,
        to: selectedPlayers.to.name
      });
      
      setResults(response.data);
      setError(null);
    } catch (err) {
      setError(err.response?.data || 'An error occurred during the search');
      setResults(null);
    } finally {
      setLoading(false);
    }
  };

  return (
    <Container component="main" maxWidth="lg">
      <CssBaseline />
      <Typography variant="h3" component="h1" gutterBottom align="center" sx={{ mt: 4 }}>
        Player Connection Visualizer
      </Typography>

      <Grid container spacing={3} sx={{ mb: 4 }}>
        <Grid item xs={6}>
          <FormControlLabel
            control={
              <Switch
                checked={sport === 'soccer'}
                onChange={() => setSport(sport === 'basketball' ? 'soccer' : 'basketball')}
              />
            }
            label={`Switch to ${sport === 'basketball' ? 'Soccer' : 'Basketball'}`}
          />
        </Grid>
        <Grid item xs={6}>
          <FormControlLabel
            control={
              <Switch
                checked={showBothAlgorithms}
                onChange={(e) => setShowBothAlgorithms(e.target.checked)}
              />
            }
            label="Compare both algorithms"
          />
        </Grid>
      </Grid>

      <PlayerSearchForm
        sport={sport}
        players={players}
        selectedPlayers={selectedPlayers}
        onSelect={(player, type) => setSelectedPlayers(prev => ({ ...prev, [type]: player }))}
        onSearch={handleSearch}
        loading={loading}
      />

      {error && (
        <Alert severity="error" sx={{ mt: 2 }}>
          {error}
        </Alert>
      )}

      {loading && <CircularProgress sx={{ display: 'block', mx: 'auto', mt: 4 }} />}

      {results && (
        <PathDisplay
          results={results}
          sport={sport}
          showBoth={showBothAlgorithms}
          sx={{ mt: 4 }}
        />
      )}
    </Container>
  );
};

export default App;