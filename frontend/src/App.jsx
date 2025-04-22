// App.jsx
import React, { useState, useEffect } from 'react';
import axios from 'axios';
import {
  Box,
  Container,
  Typography,
  Grid,
  FormControlLabel,
  Switch,
  CircularProgress,
  Alert,
  CssBaseline,
  Paper,
  FormControl,
  InputLabel,
  Select,
  MenuItem,
  Button,
  Icon,
} from '@mui/material';
import { styled } from '@mui/material/styles';
import PathDisplay from './components/PathDisplay';

const API_ROOT = 'http://localhost:18080';

const StyledPaper = styled(Paper)(({ theme }) => ({
  maxWidth: 1300,
  width: '100%',
  borderRadius: 12,
  boxShadow: theme.shadows[6],
  padding: theme.spacing(6), 
  display: 'flex',
  flexDirection: 'column',
  alignItems: 'center',
  gap: theme.spacing(5),
}));

const StyledFormControlLabel = styled(FormControlLabel)(({ theme }) => ({
  marginRight: theme.spacing(4),
}));

const StyledFormControl = styled(FormControl)(({ theme }) => ({
  flex: 1,
  margin: theme.spacing(1, 0),
}));

const StyledButton = styled(Button)(({ theme }) => ({
  padding: theme.spacing(2, 5),
  fontSize: '1.2rem',
}));

const InfoBox = styled(Box)(({ theme }) => ({
  backgroundColor: '#e0f7fa',
  color: '#00acc1',
  padding: theme.spacing(2),
  borderRadius: theme.shape.borderRadius,
  textAlign: 'center',
  fontSize: '0.9rem',
  marginTop: theme.spacing(3),
  maxWidth: 850,
  width: '100%',
  boxSizing: 'border-box',
  display: 'flex',
  alignItems: 'center',
  justifyContent: 'center',
}));

export default function App() {
  const [sport, setSport] = useState('basketball');
  const [compareAlgos, setCompareAlgos] = useState(true);
  const [players, setPlayers] = useState([]);
  const [selectedFrom, setSelectedFrom] = useState('');
  const [selectedTo, setSelectedTo] = useState('');
  const [results, setResults] = useState(null);
  const [error, setError] = useState(null);
  const [loading, setLoading] = useState(false);
  const [showInfoBox, setShowInfoBox] = useState(true);

  useEffect(() => {
    (async () => {
      try {
        setLoading(true);
        const endpoint = sport === 'basketball' ? '/bball_graph' : '/fball_graph';
        const { data } = await axios.get(`${API_ROOT}${endpoint}`);
        setPlayers(data.players || []);
        setError(null);
      } catch (e) {
        setError('Failed to fetch players. Please try again later.');
        setPlayers([]);
      } finally {
        setLoading(false);
      }
    })();
    setSelectedFrom('');
    setSelectedTo('');
    setResults(null);
    setShowInfoBox(true);
  }, [sport]);

  /* ------------------------------ search path ------------------------------ */
  const handleSearch = async () => {
    if (!selectedFrom || !selectedTo) {
      setError('Please select both players');
      return;
    }
    if (selectedFrom === selectedTo) {
      setError('Please select two different players');
      return;
    }
    setLoading(true);
    try {
      const endpoint = sport === 'basketball' ? '/bballAlgo' : '/fballAlgo';
      const { data } = await axios.post(`${API_ROOT}${endpoint}`, {
        from: selectedFrom,
        to: selectedTo,
      });
      setResults(data);
      setError(null);
    } catch (e) {
      setError(e.response?.data || 'An error occurred during the search');
      setResults(null);
    } finally {
      setLoading(false);
    }
  };

  useEffect(() => {
    if (selectedFrom && selectedTo && selectedFrom !== selectedTo) {
      setShowInfoBox(false);
    } else {
      setShowInfoBox(true);
    }
  }, [selectedFrom, selectedTo]);

  return (
    <Container disableGutters maxWidth={false} sx={{ minHeight: '100vh', p: 4,
      display:'flex', justifyContent:'center', alignItems:'center', bgcolor:'#f9fafb' }}>
      <CssBaseline />
      <StyledPaper>
        <Typography variant="h3" align="center" fontWeight={600} mb={4}>
          Player&nbsp;Connection&nbsp;Visualizer
        </Typography>

        <Box sx={{ display: 'flex', gap: 4, mb: 4, justifyContent: 'center', flexWrap: 'wrap' }}> 
          <StyledFormControlLabel
            label={`Switch to ${sport === 'basketball' ? 'Soccer' : 'Basketball'}`}
            control={
              <Switch
                checked={sport === 'soccer'}
                onChange={() =>
                  setSport(prev => (prev === 'basketball' ? 'soccer' : 'basketball'))
                }
              />
            }
          />
          <StyledFormControlLabel
            label="Compare both algorithms"
            control={
              <Switch
                checked={compareAlgos}
                onChange={e => setCompareAlgos(e.target.checked)}
              />
            }
          />
        </Box>

        <Box sx={{ display: 'flex', gap: 3, width: '100%', maxWidth: 850, flexWrap: 'wrap', justifyContent: 'center' }}>
          <StyledFormControl fullWidth>
            <InputLabel id="select-player-a-label">Select Player A</InputLabel>
            <Select
              labelId="select-player-a-label"
              id="playerA"
              value={selectedFrom}
              label="Select Player A"
              onChange={(e) => setSelectedFrom(e.target.value)}
            >
              <MenuItem value="" disabled>Select Player A</MenuItem>
              {players.map((player) => (
                <MenuItem key={player.id} value={player.name}>
                  {player.name}
                </MenuItem>
              ))}
            </Select>
          </StyledFormControl>

          <StyledFormControl fullWidth>
            <InputLabel id="select-player-b-label">Select Player B</InputLabel>
            <Select
              labelId="select-player-b-label"
              id="playerB"
              value={selectedTo}
              label="Select Player B"
              onChange={(e) => setSelectedTo(e.target.value)}
            >
              <MenuItem value="" disabled>Select Player B</MenuItem>
              {players.map((player) => (
                <MenuItem key={player.id} value={player.name}>
                  {player.name}
                </MenuItem>
              ))}
            </Select>
          </StyledFormControl>

          <StyledButton
            variant="contained"
            color="primary"
            onClick={handleSearch}
            disabled={!selectedFrom || !selectedTo || selectedFrom === selectedTo || loading}
          >
            Find Path
          </StyledButton>
        </Box>

        {showInfoBox && (
          <InfoBox>
            Select two players to visualize their connection
          </InfoBox>
        )}

        {error && <Alert severity="error" sx={{ mt: 3, width: '100%', maxWidth: 850 }}>{error}</Alert>}
        {loading && <CircularProgress sx={{ display:'block', mx:'auto', mt:4 }} />}

        {results && (
          <PathDisplay
            results={results}
            sport={sport}
            showBoth={compareAlgos}
            sx={{ mt: 4, width: '100%', maxWidth: 850 }}
          />
        )}
      </StyledPaper>
    </Container>
  );
}